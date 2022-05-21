//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_COLLECTION_REVERSE_ITERATOR_IMPL_HPP__
#define __CDS_COLLECTION_REVERSE_ITERATOR_IMPL_HPP__

//namespace cds { // NOLINT(modernize-concat-nested-namespaces)
//    namespace experimental {
//
//        template < typename T >
//        constexpr Collection < T > :: ReverseIterator :: ReverseIterator (
//                Collection < T >                   const * pCollection,
//                UniquePointer < DelegateIterator >      && pIterator
//        ) noexcept :
//                Collection < T > :: AbstractIterator (
//                        pCollection,
//                        UniquePointer < AbstractDelegateIterator > ( cds :: forward < UniquePointer < DelegateIterator > > ( pIterator ) )
//                ) {
//
//        }
//
//        template < typename T >
//        __CDS_OptimalInline Collection < T > :: ReverseIterator :: ReverseIterator (
//                ReverseIterator const & iterator
//        ) noexcept :
//                AbstractIterator ( iterator ) {
//
//        }
//
//        template < typename T >
//        constexpr Collection < T > :: ReverseIterator :: ReverseIterator (
//                ReverseIterator && iterator
//        ) noexcept :
//                AbstractIterator ( cds :: forward < AbstractIterator > ( iterator ) ) {
//
//        }
//
//        template < typename T >
//        __CDS_OptimalInline auto Collection < T > :: ReverseIterator :: operator = ( ReverseIterator const & iterator ) noexcept -> ReverseIterator & {
//            if ( this == & iterator ) {
//                return * this;
//            }
//
//            this->_pDelegate    = iterator._pDelegate->copy();
//            this->_pCollection  = iterator._pCollection;
//            return * this;
//        }
//
//        template < typename T >
//        __CDS_cpplang_NonConstConstexprMemberFunction auto Collection < T > :: ReverseIterator :: operator = ( ReverseIterator && iterator ) noexcept -> ReverseIterator & {
//            if ( this == & iterator ) {
//                return * this;
//            }
//
//            this->_pDelegate    = std :: move ( iterator._pDelegate );
//            this->_pCollection  = std :: move ( iterator._pCollection );
//            return * this;
//        }
//
//        template < typename T >
//        __CDS_cpplang_ConstexprOverride auto Collection < T > :: ReverseIterator :: operator -> () const noexcept -> ElementType * {
//            return & ( * ( * this ) );
//        }
//
//        template < typename T >
//        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ReverseIterator :: operator ++ () noexcept -> ReverseIterator & {
//            (void) this->next();
//            return * this;
//        }
//
//        template < typename T >
//        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ReverseIterator :: operator ++ (int) noexcept -> ReverseIterator {
//            auto copy = * this;
//            (void) this->next();
//            return copy;
//        }
//
//        template < typename T >
//        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ReverseIterator :: operator -- () noexcept -> ReverseIterator & {
//            (void) this->previous();
//            return * this;
//        }
//
//        template < typename T >
//        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ReverseIterator :: operator -- (int) noexcept -> ReverseIterator {
//            auto copy = * this;
//            (void) this->previous();
//            return copy;
//        }
//
//        template < typename T >
//        __CDS_cpplang_ConstexprPureAbstract auto Collection < T > :: ReverseIterator :: operator * () const noexcept -> ElementType & {
//            return reinterpret_cast < DelegateIterator const * > ( this->_pDelegate.get() )->value();
//        }
//
//    }
//}

#endif // __CDS_COLLECTION_REVERSE_ITERATOR_IMPL_HPP__
