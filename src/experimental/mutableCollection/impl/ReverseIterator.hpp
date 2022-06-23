//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_MUTABLE_COLLECTION_REVERSE_ITERATOR_IMPL_HPP__
#define __CDS_MUTABLE_COLLECTION_REVERSE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr MutableCollection < __ElementType > :: ReverseIterator :: ReverseIterator (
                MutableCollection < __ElementType >        const * pCollection,
                cds :: UniquePointer < DelegateIterator >       && pIterator
        ) noexcept :
                MutableCollection < __ElementType > :: AbstractIterator (
                        pCollection,
                        cds :: UniquePointer < AbstractDelegateIterator > (
                                cds :: forward < cds :: UniquePointer < DelegateIterator > > (
                                        pIterator
                                )
                        )
                ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline MutableCollection < __ElementType > :: ReverseIterator :: ReverseIterator (
                ReverseIterator const & iterator
        ) noexcept :
                MutableCollection < __ElementType > :: AbstractIterator ( iterator ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        constexpr MutableCollection < __ElementType > :: ReverseIterator :: ReverseIterator (
                ReverseIterator && iterator
        ) noexcept :
                MutableCollection < __ElementType > :: AbstractIterator ( std :: move ( iterator ) ) {

        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto MutableCollection < __ElementType > :: ReverseIterator :: operator = (
                ReverseIterator const & iterator
        ) noexcept -> ReverseIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = iterator._pDelegate->copy();
            this->_pCollection  = iterator._pCollection;
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto MutableCollection < __ElementType > :: ReverseIterator :: operator = (
                ReverseIterator && iterator
        ) noexcept -> ReverseIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = std :: move ( iterator._pDelegate );
            this->_pCollection  = std :: exchange ( iterator._pCollection, nullptr );
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto MutableCollection < __ElementType > :: ReverseIterator :: operator -> () const noexcept -> __ElementType * {

            return & ( * ( * this ) );
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto MutableCollection < __ElementType > :: ReverseIterator :: operator ++ () noexcept -> ReverseIterator & {

            (void) this->next();
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto MutableCollection < __ElementType > :: ReverseIterator :: operator ++ (int) noexcept -> ReverseIterator {

            auto copy = * this;
            (void) this->next();
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto MutableCollection < __ElementType > :: ReverseIterator :: operator -- () noexcept -> ReverseIterator & {

            (void) this->previous();
            return * this;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto MutableCollection < __ElementType > :: ReverseIterator :: operator -- (int) noexcept -> ReverseIterator {

            auto copy = * this;
            (void) this->previous();
            return copy;
        }


        template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto MutableCollection < __ElementType > :: ReverseIterator :: operator * () const noexcept -> __ElementType & {

            return reinterpret_cast < DelegateIterator const * > ( this->_pDelegate.get() )->value();
        }

    }
}

#endif // __CDS_MUTABLE_COLLECTION_REVERSE_ITERATOR_IMPL_HPP__
