//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_CONST_REVERSE_ITERATOR_IMPL_HPP__
#define __CDS_COLLECTION_CONST_REVERSE_ITERATOR_IMPL_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr Collection < __ElementType > :: ConstReverseIterator :: ConstReverseIterator (
            Collection < __ElementType >                   const * pCollection,
            cds :: UniquePointer < DelegateConstIterator >      && pIterator
    ) noexcept :
            Collection < __ElementType > :: AbstractIterator (
                    pCollection,
                    cds :: UniquePointer < AbstractDelegateIterator > (
                            cds :: forward < cds :: UniquePointer < DelegateConstIterator > > (
                                    pIterator
                            )
                    )
            ) {

    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline Collection < __ElementType > :: ConstReverseIterator :: ConstReverseIterator (
            ConstReverseIterator const & iterator
    ) noexcept :
            Collection < __ElementType > :: AbstractIterator ( iterator ) {

    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr Collection < __ElementType > :: ConstReverseIterator :: ConstReverseIterator (
            ConstReverseIterator && iterator
    ) noexcept :
            Collection < __ElementType > :: AbstractIterator ( std :: move ( iterator ) ) {

    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Collection < __ElementType > :: ConstReverseIterator :: operator = (
            ConstReverseIterator const & iterator
    ) noexcept -> ConstReverseIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pDelegate    = iterator._pDelegate->copy();
        this->_pCollection  = iterator._pCollection;
        return * this;
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Collection < __ElementType > :: ConstReverseIterator :: operator = (
            ConstReverseIterator && iterator
    ) noexcept -> ConstReverseIterator & {

        if ( this == & iterator ) {
            return * this;
        }

        this->_pDelegate    = std :: move ( iterator._pDelegate );
        this->_pCollection  = std :: exchange ( iterator._pCollection, nullptr );
        return * this;
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Collection < __ElementType > :: ConstReverseIterator :: operator -> () const noexcept -> __ElementType const * {

        return & ( * ( * this ) );
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Collection < __ElementType > :: ConstReverseIterator :: operator ++ () noexcept -> ConstReverseIterator & {

        (void) this->next();
        return * this;
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Collection < __ElementType > :: ConstReverseIterator :: operator ++ (int) noexcept -> ConstReverseIterator {

        auto copy = * this;
        (void) this->next();
        return copy;
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Collection < __ElementType > :: ConstReverseIterator :: operator -- () noexcept -> ConstReverseIterator & {

        (void) this->previous();
        return * this;
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Collection < __ElementType > :: ConstReverseIterator :: operator -- (int) noexcept -> ConstReverseIterator {

        auto copy = * this;
        (void) this->previous();
        return copy;
    }

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Collection < __ElementType > :: ConstReverseIterator :: operator * () const noexcept -> ElementType const & {

        return reinterpret_cast < DelegateConstIterator const * > ( this->_pDelegate.get() )->value();
    }

}

#endif // __CDS_COLLECTION_CONST_REVERSE_ITERATOR_IMPL_HPP__
