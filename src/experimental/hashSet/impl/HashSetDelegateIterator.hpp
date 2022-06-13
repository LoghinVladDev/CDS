//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_EX_HASH_SET_DELEGATE_ITERATOR_IMPL_HPP__
#define __CDS_EX_HASH_SET_DELEGATE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: HashSetDelegateIterator (
                Node const * pNode
        ) noexcept :
                DelegateConstIterator (),
                _pNode ( pNode ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: HashSetDelegateIterator (
                HashSetDelegateIterator const & iterator
        ) noexcept :
                DelegateConstIterator (),
                _pNode ( iterator._pNode ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: HashSetDelegateIterator (
                HashSetDelegateIterator && iterator
        ) noexcept :
                DelegateConstIterator (),
                _pNode ( cds :: exchange ( iterator._pNode, nullptr ) ) {

        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        constexpr auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: node () const noexcept -> Node const * {

            return this->_pNode;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: valid () const noexcept -> bool {

            return this->_pNode != nullptr;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: next () noexcept -> HashSetDelegateIterator & {

            this->_pNode = this->_pNode->_pNext;
            return * this;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: previous() noexcept -> HashSetDelegateIterator & {

            this->_pNode = this->_pNode->_pNext;
            return * this;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: value () const noexcept -> __ElementType const & {

            return * this->_pNode->_pData;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: equals (
                AbstractDelegateIterator const & iterator
        ) const noexcept -> bool {

            if ( this == & iterator ) {
                return true;
            }

            return reinterpret_cast < decltype ( this ) > ( & iterator )->_pNode == this->_pNode;
        }


        template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: copy () const noexcept -> HashSetDelegateIterator * {

            return cds :: copy ( * this );
        }

    }
}

#endif // __CDS_EX_HASH_SET_DELEGATE_ITERATOR_IMPL_HPP__
