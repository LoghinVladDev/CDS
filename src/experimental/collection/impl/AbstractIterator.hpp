//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_ABSTRACT_ITERATOR_IMPL_HPP__
#define __CDS_COLLECTION_ABSTRACT_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        constexpr Collection < T > :: AbstractIterator :: AbstractIterator (
                Collection < T >                            const * pCollection,
                UniquePointer < AbstractDelegateIterator >       && pIterator
        ) noexcept :
                _pCollection ( pCollection ),
                _pDelegate ( cds :: forward < UniquePointer < AbstractDelegateIterator > > ( pIterator ) ) {

        }

        template < typename T >
        __CDS_OptimalInline Collection < T > :: AbstractIterator :: AbstractIterator (
                AbstractIterator const & iterator
        ) noexcept :
                _pCollection ( iterator._pCollection ),
                _pDelegate ( iterator._pDelegate->copy() ) {

        }

        template < typename T >
        constexpr Collection < T > :: AbstractIterator :: AbstractIterator (
                AbstractIterator && iterator
        ) noexcept :
                _pCollection ( std :: move ( iterator._pCollection ) ),
                _pDelegate ( std :: move ( iterator._pDelegate ) ) {

        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Collection < T > :: AbstractIterator :: equals ( AbstractIterator const & iterator ) const noexcept -> bool {
            return
                    this->_pCollection == iterator._pCollection &&
                    this->_pDelegate->equals ( * iterator._pDelegate );
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Collection < T > :: AbstractIterator :: operator == ( AbstractIterator const & iterator ) const noexcept -> bool {
            return this->equals ( iterator );
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Collection < T > :: AbstractIterator :: operator != ( AbstractIterator const & iterator ) const noexcept -> bool {
            return ! this->equals ( iterator );
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: AbstractIterator :: next () noexcept -> AbstractIterator & {
            (void) this->_pDelegate->next();
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: AbstractIterator :: previous () noexcept -> AbstractIterator & {
            (void) this->_pDelegate->previous();
            return * this;
        }

        template < typename T >
        constexpr auto Collection < T > :: AbstractIterator :: of ( Collection < T > const * pCollection ) const noexcept -> bool {
            return this->_pCollection == pCollection;
        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: AbstractIterator :: valid () const noexcept -> bool {
            return
                    this->_pDelegate != nullptr &&
                    this->_pDelegate->valid();
        }

    }
}

#endif // __CDS_COLLECTION_ABSTRACT_ITERATOR_IMPL_HPP__
