//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_ITERATOR_IMPL_HPP__
#define __CDS_COLLECTION_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        constexpr Collection < T > :: Iterator :: Iterator (
                Collection < T >                   const * pCollection,
                UniquePointer < DelegateIterator >      && pIterator
        ) noexcept :
                Collection < T > :: AbstractIterator (
                        pCollection,
                        UniquePointer < AbstractDelegateIterator > ( cds :: forward < UniquePointer < DelegateIterator > > ( pIterator ) )
                ) {

        }

        template < typename T >
        __CDS_OptimalInline Collection < T > :: Iterator :: Iterator (
                Iterator const & iterator
        ) noexcept :
                AbstractIterator ( iterator ) {

        }

        template < typename T >
        constexpr Collection < T > :: Iterator :: Iterator (
                Iterator && iterator
        ) noexcept :
                AbstractIterator ( cds :: forward < AbstractIterator > ( iterator ) ) {

        }

        template < typename T >
        __CDS_OptimalInline auto Collection < T > :: Iterator :: operator = ( Iterator const & iterator ) noexcept -> Iterator & {
            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = copy ( iterator._pDelegate.get() );
            this->_pCollection  = iterator._pCollection;
            return * this;
        }

        template < typename T >
        __CDS_cpplang_NonConstConstexprMemberFunction auto Collection < T > :: Iterator :: operator = ( Iterator && iterator ) noexcept -> Iterator & {
            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = std :: move ( iterator._pDelegate );
            this->_pCollection  = std :: move ( iterator._pCollection );
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Collection < T > :: Iterator :: operator -> () const noexcept -> ElementType * {
            return & ( * ( * this ) );
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: Iterator :: operator ++ () noexcept -> Iterator & {
            (void) this->next();
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: Iterator :: operator ++ (int) noexcept -> Iterator {
            auto copy = * this;
            (void) this->next();
            return copy;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: Iterator :: operator -- () noexcept -> Iterator & {
            (void) this->previous();
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: Iterator :: operator -- (int) noexcept -> Iterator {
            auto copy = * this;
            (void) this->previous();
            return copy;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: Iterator :: operator * () const noexcept -> ElementType & {
            return reinterpret_cast < DelegateIterator const * > ( this->_pDelegate.get() )->value();
        }

    }
}

#endif // __CDS_COLLECTION_ITERATOR_IMPL_HPP__
