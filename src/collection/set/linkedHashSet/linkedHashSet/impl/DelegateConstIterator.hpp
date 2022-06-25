//
// Created by loghin on 6/25/22.
//

#ifndef __CDS_LINKED_HASH_SET_DELEGATE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_LINKED_HASH_SET_DELEGATE_CONST_ITERATOR_IMPL_HPP__

namespace cds {

    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    constexpr LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: LinkedHashSetDelegateConstIterator (
            SingleLinkedListConstIterator const & iterator
    ) noexcept :
            _iterator ( iterator ) {

    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    constexpr LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: LinkedHashSetDelegateConstIterator (
            LinkedHashSetDelegateConstIterator const & iterator
    ) noexcept :
            _iterator ( iterator._iterator ) {

    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    constexpr LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: LinkedHashSetDelegateConstIterator (
            LinkedHashSetDelegateConstIterator && iterator
    ) noexcept :
            _iterator ( std :: move ( iterator._iterator ) ) {

    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: valid () const noexcept -> bool {

        return static_cast < bool > ( this->_iterator );
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    constexpr auto LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: iterator () const noexcept -> SingleLinkedListConstIterator const & {

        return this->_iterator;
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: next () noexcept -> LinkedHashSetDelegateConstIterator & {

        (void) ++ this->_iterator;
        return * this;
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: previous() noexcept -> LinkedHashSetDelegateConstIterator & {

        return this->next();
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: value () const noexcept -> __ElementType const & {

        return * ( * this->_iterator );
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: equals (
            AbstractDelegateIterator const & iterator
    ) const noexcept -> bool {

        return reinterpret_cast < decltype ( this ) > ( & iterator )->_iterator == this->_iterator;
    }


    template < typename __ElementType, typename __HashCalculator > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto LinkedHashSet < __ElementType, __HashCalculator > :: LinkedHashSetDelegateConstIterator :: copy () const noexcept -> LinkedHashSetDelegateConstIterator * {

        return cds :: copy ( * this );
    }

}

#endif // __CDS_LINKED_HASH_SET_DELEGATE_CONST_ITERATOR_IMPL_HPP__
