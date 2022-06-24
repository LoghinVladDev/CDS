//
// Created by loghin on 4/27/22.
//

#ifndef __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: LinkedListDelegateConstIterator (
                LinkedList < __ElementType > :: Node    const * pNode,
                bool                                            forward
        ) noexcept :
                DelegateConstIterator (),
                _pNode ( pNode ),
                _forward ( forward ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: LinkedListDelegateConstIterator (
                LinkedListDelegateConstIterator const & iterator
        ) noexcept :
                DelegateConstIterator (),
                _pNode ( iterator._pNode ),
                _forward ( iterator._forward ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: LinkedListDelegateConstIterator (
                LinkedListDelegateConstIterator && iterator
        ) noexcept :
                DelegateConstIterator (),
                _pNode ( cds :: exchange ( iterator._pNode, nullptr ) ),
                _forward ( cds :: exchange ( iterator._forward, true ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: node () const noexcept -> LinkedList < __ElementType > :: Node const * {

            return this->_pNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: valid () const noexcept -> bool {

            return this->_pNode != nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: next () noexcept -> LinkedListDelegateConstIterator & {

            (void) ( this->_forward ? ( this->_pNode = this->_pNode->_pNext ) : ( this->_pNode = this->_pNode->_pPrevious ) );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: previous () noexcept -> LinkedListDelegateConstIterator & {

            (void) ( this->_forward ? ( this->_pNode = this->_pNode->_pPrevious ) : ( this->_pNode = this->_pNode->_pNext ) );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: value () const noexcept -> __ElementType const & {

            return this->_pNode->_data.data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool {

            if ( this == & iterator ) {
                return true;
            }

            return reinterpret_cast < decltype ( this ) > ( & iterator )->_pNode == this->_pNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto LinkedList < __ElementType > :: LinkedListDelegateConstIterator :: copy () const noexcept -> LinkedListDelegateConstIterator * {

            return cds :: copy ( * this );
        }

    }
}

#endif // __CDS_LINKED_LIST_LINKED_LIST_DELEGATE_CONST_ITERATOR_IMPL_HPP__
