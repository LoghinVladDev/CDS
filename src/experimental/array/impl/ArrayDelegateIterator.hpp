//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_ARRAY_DELEGATE_ITERATOR_IMPL_HPP__
#define __CDS_ARRAY_ARRAY_DELEGATE_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename T >
        constexpr Array < T > :: ArrayDelegateIterator :: ArrayDelegateIterator (
                Array * pArray,
                Index   index,
                bool    forward
        ) noexcept :
                DelegateIterator (),
                _pArray ( pArray ),
                _index ( index ),
                _forward ( forward ) {

        }

        template < typename T >
        constexpr Array < T > :: ArrayDelegateIterator :: ArrayDelegateIterator (
                ArrayDelegateIterator const & iterator
        ) noexcept :
                DelegateIterator (),
                _pArray ( iterator._pArray ),
                _index ( iterator._index ),
                _forward ( iterator._forward ) {

        }

        template < typename T >
        constexpr Array < T > :: ArrayDelegateIterator :: ArrayDelegateIterator (
                ArrayDelegateIterator && iterator
        ) noexcept :
                DelegateIterator (),
                _pArray ( cds :: exchange ( iterator._pArray, nullptr ) ),
                _index ( cds :: exchange ( iterator._index, 0 ) ),
                _forward ( cds :: exchange ( iterator._forward, true ) ) {

        }

        template < typename T >
        constexpr auto Array < T > :: ArrayDelegateIterator :: index () const noexcept -> Index {
            return this->_index;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: ArrayDelegateIterator :: valid () const noexcept -> bool {
            return
                    this->_pArray != nullptr &&
                    this->_index >= 0 && this->_index < this->_pArray->size();
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: ArrayDelegateIterator :: next () noexcept -> ArrayDelegateIterator & {
            (void) ( this->_forward ? ( ++ this->_index ) : ( -- this->_index ) );
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: ArrayDelegateIterator :: previous () noexcept -> ArrayDelegateIterator & {
            (void) ( this->_forward ? ( -- this->_index ) : ( ++ this->_index ) );
            return * this;
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: ArrayDelegateIterator :: value () const noexcept -> ElementType & {
            return * this->_pArray->_pData [ this->_index ];
        }

        template < typename T >
        __CDS_cpplang_ConstexprOverride auto Array < T > :: ArrayDelegateIterator :: equals ( AbstractDelegateIterator const & iterator ) const noexcept -> bool {
            if ( this == & iterator ) {
                return true;
            }

            auto pObject = reinterpret_cast < decltype ( this ) > ( & iterator );
            return this->_pArray == pObject->_pArray && this->_index == pObject->_index;
        }

    }
}

#endif // __CDS_ARRAY_ARRAY_DELEGATE_ITERATOR_IMPL_HPP__
