//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_LIST_ITERATOR_IMPL_HPP__
#define __CDS_LIST_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        constexpr List < T > :: Iterator :: Iterator (
                List < T >                         const * pList,
                cds :: UniquePointer < DelegateIterator >      && pIterator
        ) noexcept :
                List < T > :: AbstractIterator (
                        pList,
                        cds :: UniquePointer < AbstractDelegateIterator > ( cds :: forward < cds :: UniquePointer < DelegateIterator > > ( pIterator ) )
                ) {

        }

        template < typename T >
        __CDS_OptimalInline List < T > :: Iterator :: Iterator (
                Iterator const & iterator
        ) noexcept :
                AbstractIterator ( iterator ) {

        }

        template < typename T >
        constexpr List < T > :: Iterator :: Iterator (
                Iterator && iterator
        ) noexcept :
                AbstractIterator ( cds :: forward < AbstractIterator > ( iterator ) ) {

        }

        template < typename T >
        __CDS_OptimalInline auto List < T > :: Iterator :: operator = ( Iterator const & iterator ) noexcept -> Iterator & {
            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = iterator._pDelegate->copy();
            this->_pCollection  = iterator._pCollection;
            return * this;
        }

        template < typename T >
        __CDS_cpplang_NonConstConstexprMemberFunction auto List < T > :: Iterator :: operator = ( Iterator && iterator ) noexcept -> Iterator & {
            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = std :: move ( iterator._pDelegate );
            this->_pCollection  = std :: move ( iterator._pCollection );
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto List < T > :: Iterator :: operator -> () const noexcept -> ElementType * {
            return & ( * ( * this ) );
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto List < T > :: Iterator :: operator ++ () noexcept -> Iterator & {
            (void) this->next();
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto List < T > :: Iterator :: operator ++ (int) noexcept -> Iterator {
            auto copy = * this;
            (void) this->next();
            return copy;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto List < T > :: Iterator :: operator -- () noexcept -> Iterator & {
            (void) this->previous();
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto List < T > :: Iterator :: operator -- (int) noexcept -> Iterator {
            auto copy = * this;
            (void) this->previous();
            return copy;
        }

        template < typename T >
        __CDS_cpplang_ConstexprPureAbstract auto List < T > :: Iterator :: operator * () const noexcept -> ElementType & {
            return reinterpret_cast < DelegateIterator const * > ( this->_pDelegate.get() )->value();
        }

    }
}

#endif // __CDS_LIST_ITERATOR_IMPL_HPP__
