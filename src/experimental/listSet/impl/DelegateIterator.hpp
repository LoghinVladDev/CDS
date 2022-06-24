//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_LIST_SET_DELEGATE_ITERATOR_HPP_IMPL__
#define __CDS_LIST_SET_DELEGATE_ITERATOR_HPP_IMPL__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ListSet < __ElementType > :: ListSetDelegateIterator :: ListSetDelegateIterator (
                Node                        const * pCurrentNode,
                Node                        const * pPreviousNode
        ) noexcept :
                _pCurrentNode ( pCurrentNode ),
                _pPreviousNode ( pPreviousNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ListSet < __ElementType > :: ListSetDelegateIterator :: ListSetDelegateIterator (
                ListSetDelegateIterator const & iterator
        ) noexcept :
                _pCurrentNode ( iterator._pCurrentNode ),
                _pPreviousNode ( iterator._pPreviousNode ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr ListSet < __ElementType > :: ListSetDelegateIterator :: ListSetDelegateIterator (
                ListSetDelegateIterator && iterator
        ) noexcept :
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) ),
                _pPreviousNode ( cds :: exchange ( iterator._pPreviousNode, nullptr ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ListSet < __ElementType > :: ListSetDelegateIterator :: valid () const noexcept -> bool {

            return this->_pCurrentNode != nullptr;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ListSet < __ElementType > :: ListSetDelegateIterator :: previousNode() const noexcept -> Node const * {

            return this->_pPreviousNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto ListSet < __ElementType > :: ListSetDelegateIterator :: currentNode() const noexcept -> Node const * {

            return this->_pCurrentNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto ListSet < __ElementType > :: ListSetDelegateIterator :: next() noexcept -> ListSetDelegateIterator & {

            this->_pPreviousNode    = this->_pCurrentNode;
            this->_pCurrentNode     = this->_pCurrentNode->_pNext;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto ListSet < __ElementType > :: ListSetDelegateIterator :: previous() noexcept -> ListSetDelegateIterator & {

            return this->next();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto ListSet < __ElementType > :: ListSetDelegateIterator :: value() const noexcept -> __ElementType const & {

            return this->_pCurrentNode->_data.data();
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto ListSet < __ElementType > :: ListSetDelegateIterator :: equals(
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool {

            return reinterpret_cast < decltype (this) > ( & iterator )->_pCurrentNode == this->_pCurrentNode;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto ListSet < __ElementType > :: ListSetDelegateIterator :: copy() const noexcept -> ListSetDelegateIterator * {

            return cds :: copy ( * this );
        }

    }
}

#endif // __CDS_LIST_SET_DELEGATE_ITERATOR_HPP_IMPL__
