//
// Created by loghin on 6/13/22.
//

#ifndef __CDS_HASH_SET_DELEGATE_ITERATOR_IMPL_HPP__
#define __CDS_HASH_SET_DELEGATE_ITERATOR_IMPL_HPP__

namespace cds {

    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    constexpr HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: HashSetDelegateIterator (
            HashTableConstIterator const & iterator
    ) noexcept :
            _iterator ( iterator ) {

    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    constexpr HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: HashSetDelegateIterator (
            HashSetDelegateIterator const & iterator
    ) noexcept :
            _iterator ( iterator._iterator ) {

    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    constexpr HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: HashSetDelegateIterator (
            HashSetDelegateIterator && iterator
    ) noexcept :
            _iterator ( std :: move ( iterator._iterator ) ) {

    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: valid () const noexcept -> bool {

        return static_cast < bool > ( this->_iterator );
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    constexpr auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: iterator () const noexcept -> HashTableConstIterator const & {

        return this->_iterator;
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: next () noexcept -> HashSetDelegateIterator & {

        ++ this->_iterator;
        return * this;
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: previous() noexcept -> HashSetDelegateIterator & {

        return this->next();
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: value () const noexcept -> __ElementType const & {

        return * this->_iterator;
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: equals (
            AbstractDelegateIterator const & iterator
    ) const noexcept -> bool {

        return reinterpret_cast < decltype ( this ) > ( & iterator )->_iterator == this->_iterator;
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto HashSet < __ElementType, __HashCalculator > :: HashSetDelegateIterator :: copy () const noexcept -> HashSetDelegateIterator * {

        return cds :: copy ( * this );
    }

}

#endif // __CDS_HASH_SET_DELEGATE_ITERATOR_IMPL_HPP__
