//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_HASH_SET_DELEGATE_ITERATOR_IMPL_HPP__
#define __CDS_EX_HASH_SET_DELEGATE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: skipEmpty () noexcept -> void {

            do {
                ++ this->_currentListIndex;
            } while (
                    this->_currentListIndex < this->_pHashSet->_hashCalculator.getBoundary() &&
                    this->_pHashSet->_listArray [ this->_currentListIndex ] == nullptr
            );

            if ( this->_currentListIndex < this->_pHashSet->_hashCalculator.getBoundary() ) {
                this->_pCurrentNode = this->_pHashSet->_listArray [ this->_currentListIndex ];
            } else {
                this->_pCurrentNode = nullptr;
            }
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConstructorNonEmptyBody HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: HashSetDelegateIterator (
                HashSet < __ElementType, __HashCalculator > const * pHashSet
        ) noexcept :
                DelegateConstIterator (),
                _pHashSet ( pHashSet ),
                _currentListIndex ( -1 ) {

            if ( this->_pHashSet != nullptr && this->_pHashSet->_listArray != nullptr ) {
                this->skipEmpty();
            }
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: HashSetDelegateIterator (
                HashSetDelegateIterator const & iterator
        ) noexcept :
                DelegateConstIterator (),
                _pHashSet ( iterator._pHashSet ),
                _currentListIndex ( iterator._currentListIndex ),
                _pCurrentNode ( iterator._pCurrentNode ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: HashSetDelegateIterator (
                HashSetDelegateIterator && iterator
        ) noexcept :
                DelegateConstIterator (),
                _pHashSet ( cds :: exchange ( iterator._pHashSet, nullptr ) ),
                _currentListIndex ( cds :: exchange ( iterator._currentListIndex, 0ULL ) ),
                _pCurrentNode ( cds :: exchange ( iterator._pCurrentNode, nullptr ) )  {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: valid () const noexcept -> bool {

            return this->_pCurrentNode != nullptr;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: currentListIndex () const noexcept -> Index {

            return this->_currentListIndex;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: currentNode () const noexcept -> const Node * {

            return this->_pCurrentNode;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: next () noexcept -> HashSetDelegateIterator & {

            if ( this->_currentListIndex >= this->_pHashSet->_hashCalculator.getBoundary() ) {
                return * this;
            }

            this->_pCurrentNode = this->_pCurrentNode->_pNext;
            if ( this->_pCurrentNode == nullptr ) {
                this->skipEmpty();
            }

            return * this;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: previous() noexcept -> HashSetDelegateIterator & {

            return this->next();
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: value () const noexcept -> __ElementType const & {

            return * this->_pCurrentNode->_pData;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool {

            if ( this == & iterator ) {
                return true;
            }

            return reinterpret_cast < decltype ( this ) > ( & iterator )->_pCurrentNode == this->_pCurrentNode;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: copy () const noexcept -> HashSetDelegateIterator * {

            return cds :: copy ( * this );
        }

    }
}

#endif // __CDS_EX_HASH_SET_DELEGATE_ITERATOR_IMPL_HPP__
