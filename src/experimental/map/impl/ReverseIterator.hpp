//
// Created by loghin on 6/16/22.
//

#ifndef __CDS_MAP_REVERSE_ITERATOR_IMPL_HPP__
#define __CDS_MAP_REVERSE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: ReverseIterator :: ReverseIterator () noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: ReverseIterator :: ReverseIterator (
                Map < __KeyType, __ValueType >              const * pMap,
                cds :: UniquePointer < DelegateIterator >        && pIterator
        ) noexcept :
                Map < __KeyType, __ValueType > :: AbstractIterator (
                        pMap,
                        cds :: UniquePointer < AbstractDelegateIterator > ( cds :: forward < cds :: UniquePointer < DelegateIterator > > ( pIterator ) )
                ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline Map < __KeyType, __ValueType > :: ReverseIterator :: ReverseIterator (
                ReverseIterator const & iterator
        ) noexcept :
                Map < __KeyType, __ValueType > :: AbstractIterator ( iterator ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        constexpr Map < __KeyType, __ValueType > :: ReverseIterator :: ReverseIterator (
                ReverseIterator && iterator
        ) noexcept :
                Map < __KeyType, __ValueType > :: AbstractIterator ( std :: move ( iterator ) ) {

        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        Map < __KeyType, __ValueType > :: ReverseIterator :: ~ReverseIterator () noexcept = default;


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: ReverseIterator :: operator = (
                ReverseIterator const & iterator
        ) noexcept -> ReverseIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = iterator._pDelegate->copy();
            this->_pCollection  = iterator._pCollection;
            return * this;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: ReverseIterator :: operator = (
                ReverseIterator && iterator
        ) noexcept -> ReverseIterator & {

            if ( this == & iterator ) {
                return * this;
            }

            this->_pDelegate    = std :: move ( iterator._pDelegate );
            this->_pCollection  = std :: exchange ( iterator._pCollection, nullptr );
            return * this;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Map < __KeyType, __ValueType > :: ReverseIterator :: operator -> () const noexcept -> Map < __KeyType, __ValueType > :: EntryType * {

            return & ( * ( * this ) );
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Map < __KeyType, __ValueType > :: ReverseIterator :: operator ++ () noexcept -> ReverseIterator & {

            (void) this->next();
            return * this;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: ReverseIterator :: operator ++ (int) noexcept -> ReverseIterator {

            auto copy = * this;
            (void) this->next();
            return copy;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Map < __KeyType, __ValueType > :: ReverseIterator :: operator -- () noexcept -> ReverseIterator & {

            (void) this->previous();
            return * this;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_OptimalInline auto Map < __KeyType, __ValueType > :: ReverseIterator :: operator -- (int) noexcept -> ReverseIterator {

            auto copy = * this;
            (void) this->previous();
            return copy;
        }


        template < typename __KeyType, typename __ValueType > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprOverride auto Map < __KeyType, __ValueType > :: ReverseIterator :: operator * () const noexcept -> Map < __KeyType, __ValueType > :: EntryType & {

            return reinterpret_cast < DelegateIterator const * > ( this->_pDelegate.get() )->value();
        }

    }
}

#endif // __CDS_MAP_REVERSE_ITERATOR_IMPL_HPP__
