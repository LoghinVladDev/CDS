//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_ITERATOR_IMPL_HPP__
#define __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        constexpr LinkedList < T > :: LinkedListDelegateIterator :: LinkedListDelegateIterator (
                LinkedList < T > :: Node *  pNode,
                bool                        forward
        ) noexcept :
                DelegateIterator (),
                _pNode ( pNode ),
                _forward ( forward ) {

        }

        template < typename T >
        constexpr LinkedList < T > :: LinkedListDelegateIterator :: LinkedListDelegateIterator (
                LinkedListDelegateIterator const & iterator
        ) noexcept :
                DelegateIterator (),
                _pNode ( iterator._pNode ),
                _forward ( iterator._forward ) {

        }

        template < typename T >
        constexpr LinkedList < T > :: LinkedListDelegateIterator :: LinkedListDelegateIterator (
                LinkedListDelegateIterator && iterator
        ) noexcept :
                DelegateIterator (),
                _pNode ( std :: move ( iterator._pNode ) ),
                _forward ( cds :: exchange ( iterator._forward, true ) ) {

        }

        template < typename T >
        constexpr auto LinkedList < T > :: LinkedListDelegateIterator :: node () const noexcept -> LinkedList < T > :: Node * {
            return this->_pNode.get();
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateIterator :: valid () const noexcept -> bool {
            return this->_pNode != nullptr;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateIterator :: next () noexcept -> LinkedListDelegateIterator & {
            (void) ( this->_forward ? ( this->_pNode = this->_pNode->_pNext ) : ( this->_pNode = this->_pNode->_pPrevious ) );
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateIterator :: previous () noexcept -> LinkedListDelegateIterator & {
            (void) ( this->_forward ? ( this->_pNode = this->_pNode->_pPrevious ) : ( this->_pNode = this->_pNode->_pNext ) );
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateIterator :: value () const noexcept -> ElementType & {
            return * this->_pNode->_pData;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateIterator :: equals ( AbstractDelegateIterator const & iterator ) const noexcept -> bool {
            if ( this == & iterator ) {
                return true;
            }

            return reinterpret_cast < decltype ( this ) > ( & iterator )->_pNode == this->_pNode;
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: LinkedListDelegateIterator :: copy () const noexcept -> LinkedListDelegateIterator * {
            return cds :: copy ( * this );
        }

    }
}

#endif //__CDS_LINKED_LIST_LINKED_LIST_DELEGATE_ITERATOR_IMPL_HPP__
