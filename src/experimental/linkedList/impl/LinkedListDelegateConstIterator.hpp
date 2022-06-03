//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        constexpr LinkedList < T > :: LinkedListDelegateConstIterator :: LinkedListDelegateConstIterator (
                LinkedList < T > :: Node    const * pNode,
                bool                                forward
        ) noexcept :
                DelegateConstIterator (),
                _pNode ( pNode ),
                _forward ( forward ) {

        }

        template < typename T >
        constexpr LinkedList < T > :: LinkedListDelegateConstIterator :: LinkedListDelegateConstIterator (
                LinkedListDelegateConstIterator const & iterator
        ) noexcept :
                DelegateConstIterator (),
                _pNode ( iterator._pNode ),
                _forward ( iterator._forward ) {

        }

        template < typename T >
        constexpr LinkedList < T > :: LinkedListDelegateConstIterator :: LinkedListDelegateConstIterator (
                LinkedListDelegateConstIterator && iterator
        ) noexcept :
                DelegateConstIterator (),
                _pNode ( cds :: exchange ( iterator._pNode, nullptr ) ),
                _forward ( cds :: exchange ( iterator._forward, true ) ) {

        }

        template < typename T >
        constexpr auto LinkedList < T > :: LinkedListDelegateConstIterator :: node () const noexcept -> LinkedList < T > :: Node const * {
            return this->_pNode;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateConstIterator :: valid () const noexcept -> bool {
            return this->_pNode != nullptr;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateConstIterator :: next () noexcept -> LinkedListDelegateConstIterator & {
            (void) ( this->_forward ? ( this->_pNode = this->_pNode->_pNext ) : ( this->_pNode = this->_pNode->_pPrevious ) );
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateConstIterator :: previous () noexcept -> LinkedListDelegateConstIterator & {
            (void) ( this->_forward ? ( this->_pNode = this->_pNode->_pPrevious ) : ( this->_pNode = this->_pNode->_pNext ) );
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateConstIterator :: value () const noexcept -> ElementType const & {
            return * this->_pNode->_pData;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto LinkedList < T > :: LinkedListDelegateConstIterator :: equals ( AbstractDelegateIterator const & iterator ) const noexcept -> bool {
            if ( this == & iterator ) {
                return true;
            }

            return reinterpret_cast < decltype ( this ) > ( & iterator )->_pNode == this->_pNode;
        }

        template < typename T >
        __CDS_OptimalInline auto LinkedList < T > :: LinkedListDelegateConstIterator :: copy () const noexcept -> LinkedListDelegateConstIterator * {
            return cds :: copy ( * this );
        }

    }
}

#endif // __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_IMPL_HPP__
