//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_CONST_ITERATOR_IMPL_HPP__
#define __CDS_COLLECTION_CONST_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        constexpr Collection < T > :: ConstIterator :: ConstIterator (
                Collection < T >                        const * pCollection,
                UniquePointer < DelegateConstIterator >      && pIterator
        ) noexcept :
                Collection < T > :: AbstractIterator (
                        pCollection,
                        UniquePointer < AbstractDelegateIterator > ( cds :: forward < UniquePointer < DelegateConstIterator > > ( pIterator ) )
                ) {

        }

        template < typename T >
        __CDS_OptimalInline Collection < T > :: ConstIterator :: ConstIterator (
                ConstIterator const & iterator
        ) noexcept :
                AbstractIterator ( iterator ) {

        }

        template < typename T >
        constexpr Collection < T > :: ConstIterator :: ConstIterator (
                ConstIterator && iterator
        ) noexcept :
                AbstractIterator ( cds :: forward < AbstractIterator > ( iterator ) ) {

        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: ConstIterator :: operator = ( ConstIterator const & iterator ) noexcept -> ConstIterator & {
            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = copy ( iterator._pDelegate.get() );
            this->_pCollection  = iterator._pCollection;
            return * this;
        }

        template < typename T >
        __CDS_cpplang_NonConstConstexprMemberFunction auto Collection < T > :: ConstIterator :: operator = ( ConstIterator && iterator ) noexcept -> ConstIterator & {
            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = std :: move ( iterator._pDelegate );
            this->_pCollection  = std :: move ( iterator._pCollection );
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Collection < T > :: ConstIterator :: operator -> () const noexcept -> ElementType const * {
            return & ( * ( * this ) );
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ConstIterator :: operator ++ () noexcept -> ConstIterator & {
            (void) this->next();
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ConstIterator :: operator ++ (int) noexcept -> ConstIterator {
            auto copy = * this;
            (void) this->next();
            return copy;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ConstIterator :: operator -- () noexcept -> ConstIterator & {
            (void) this->previous();
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ConstIterator :: operator -- (int) noexcept -> ConstIterator {
            auto copy = * this;
            (void) this->previous();
            return copy;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ConstIterator :: operator * () const noexcept -> ElementType const & {
            return reinterpret_cast < DelegateConstIterator const * > ( this->_pDelegate.get() )->value();
        }

    }
}

#endif // __CDS_COLLECTION_CONST_ITERATOR_IMPL_HPP__
