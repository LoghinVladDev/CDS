//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_LINKED_LIST_DELEGATE_ITERATOR_IMPL_HPP__
#define __CDS_LINKED_LIST_DELEGATE_ITERATOR_IMPL_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr LinkedList < __ElementType > :: LinkedListDelegateIterator :: LinkedListDelegateIterator (
            LinkedList < __ElementType > :: Node  * pNode,
            bool                                    forward
    ) noexcept :
            DelegateIterator (),
            _pNode ( pNode ),
            _forward ( forward ) {

    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr LinkedList < __ElementType > :: LinkedListDelegateIterator :: LinkedListDelegateIterator (
            LinkedListDelegateIterator const & iterator
    ) noexcept :
            DelegateIterator (),
            _pNode ( iterator._pNode ),
            _forward ( iterator._forward ) {

    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr LinkedList < __ElementType > :: LinkedListDelegateIterator :: LinkedListDelegateIterator (
            LinkedListDelegateIterator && iterator
    ) noexcept :
            DelegateIterator (),
            _pNode ( cds :: exchange ( iterator._pNode, nullptr ) ),
            _forward ( cds :: exchange ( iterator._forward, true ) ) {

    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto LinkedList < __ElementType > :: LinkedListDelegateIterator :: node () const noexcept -> LinkedList < __ElementType > :: Node * {

        return this->_pNode;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateIterator :: valid () const noexcept -> bool {

        return this->_pNode != nullptr;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateIterator :: next () noexcept -> LinkedListDelegateIterator & {

        (void) ( this->_forward ? ( this->_pNode = this->_pNode->_pNext ) : ( this->_pNode = this->_pNode->_pPrevious ) );
        return * this;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateIterator :: previous () noexcept -> LinkedListDelegateIterator & {

        (void) ( this->_forward ? ( this->_pNode = this->_pNode->_pPrevious ) : ( this->_pNode = this->_pNode->_pNext ) );
        return * this;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateIterator :: value () const noexcept -> __ElementType & {

        return this->_pNode->_data.data();
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateIterator :: equals (
            AbstractDelegateIterator const & iterator
    ) const noexcept -> bool {

        if ( this == & iterator ) {
            return true;
        }

        return reinterpret_cast < decltype ( this ) > ( & iterator )->_pNode == this->_pNode;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedList < __ElementType > :: LinkedListDelegateIterator :: copy () const noexcept -> LinkedListDelegateIterator * {

        return cds :: copy ( * this );
    }

}

#endif //__CDS_LINKED_LIST_DELEGATE_ITERATOR_IMPL_HPP__
