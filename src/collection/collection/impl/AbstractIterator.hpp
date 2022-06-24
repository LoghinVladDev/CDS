//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_ABSTRACT_ITERATOR_IMPL_HPP__
#define __CDS_COLLECTION_ABSTRACT_ITERATOR_IMPL_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr Collection < __ElementType > :: AbstractIterator :: AbstractIterator (
            Collection < __ElementType >                        const * pCollection,
            cds :: UniquePointer < AbstractDelegateIterator >        && pIterator
    ) noexcept :
            _pCollection ( pCollection ),
            _pDelegate ( cds :: forward < cds :: UniquePointer < AbstractDelegateIterator > > ( pIterator ) ) {

    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline Collection < __ElementType > :: AbstractIterator :: AbstractIterator (
            AbstractIterator const & iterator
    ) noexcept :
            _pCollection ( iterator._pCollection ),
            _pDelegate ( iterator._pDelegate->copy() ) {

    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr Collection < __ElementType > :: AbstractIterator :: AbstractIterator (
            AbstractIterator && iterator
    ) noexcept :
            _pCollection ( cds :: exchange ( iterator._pCollection, nullptr ) ),
            _pDelegate ( std :: move ( iterator._pDelegate ) ) {

    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Collection < __ElementType > :: AbstractIterator :: equals ( AbstractIterator const & iterator ) const noexcept -> bool {
        return
                this->_pCollection == iterator._pCollection &&
                this->_pDelegate->equals ( * iterator._pDelegate );
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Collection < __ElementType > :: AbstractIterator :: operator == ( AbstractIterator const & iterator ) const noexcept -> bool {
        return this->equals ( iterator );
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Collection < __ElementType > :: AbstractIterator :: operator != ( AbstractIterator const & iterator ) const noexcept -> bool {
        return ! this->equals ( iterator );
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprPureAbstract auto Collection < __ElementType > :: AbstractIterator :: next () noexcept -> AbstractIterator & {
        (void) this->_pDelegate->next();
        return * this;
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprPureAbstract auto Collection < __ElementType > :: AbstractIterator :: previous () noexcept -> AbstractIterator & {
        (void) this->_pDelegate->previous();
        return * this;
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto Collection < __ElementType > :: AbstractIterator :: of (
            Collection < __ElementType > const * pCollection
    ) const noexcept -> bool {

        return this->_pCollection == pCollection;
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Collection < __ElementType > :: AbstractIterator :: valid () const noexcept -> bool {
        return
                this->_pDelegate != nullptr &&
                this->_pDelegate->valid();
    }

}

#endif // __CDS_COLLECTION_ABSTRACT_ITERATOR_IMPL_HPP__
