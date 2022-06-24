//
// Created by loghin on 4/26/22.
//

#ifndef __CDS_ARRAY_DELEGATE_CONST_ITERATOR_IMPL_HPP__
#define __CDS_ARRAY_DELEGATE_CONST_ITERATOR_IMPL_HPP__

namespace cds {

    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr Array < __ElementType > :: ArrayDelegateConstIterator :: ArrayDelegateConstIterator (
            Array < __ElementType > const * pArray,
            Index                           index,
            bool                            forward
    ) noexcept :
            DelegateConstIterator (),
            _pArray ( pArray ),
            _index ( index ),
            _forward ( forward ) {

    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr Array < __ElementType > :: ArrayDelegateConstIterator :: ArrayDelegateConstIterator (
            ArrayDelegateConstIterator const & iterator
    ) noexcept :
            DelegateConstIterator (),
            _pArray ( iterator._pArray ),
            _index ( iterator._index ),
            _forward ( iterator._forward ) {

    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr Array < __ElementType > :: ArrayDelegateConstIterator :: ArrayDelegateConstIterator (
            ArrayDelegateConstIterator && iterator
    ) noexcept :
            DelegateIterator (),
            _pArray ( cds :: exchange ( iterator._pArray, nullptr ) ),
            _index ( cds :: exchange ( iterator._index, 0 ) ),
            _forward ( cds :: exchange ( iterator._forward, true ) ) {

    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto Array < __ElementType > :: ArrayDelegateConstIterator :: index () const noexcept -> Index {

        return this->_index;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: ArrayDelegateConstIterator :: valid () const noexcept -> bool {

        return
                this->_pArray != nullptr &&
                this->_index >= 0 && this->_index < this->_pArray->size();
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: ArrayDelegateConstIterator :: next () noexcept -> ArrayDelegateConstIterator & {

        (void) ( this->_forward ? ( ++ this->_index ) : ( -- this->_index ) );
        return * this;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: ArrayDelegateConstIterator :: previous () noexcept -> ArrayDelegateConstIterator & {

        (void) ( this->_forward ? ( -- this->_index ) : ( ++ this->_index ) );
        return * this;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: ArrayDelegateConstIterator :: value () const noexcept -> __ElementType const & {

        return this->_pArray->_pData [ this->_index ].data();
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprOverride auto Array < __ElementType > :: ArrayDelegateConstIterator :: equals (
            AbstractDelegateIterator const & iterator
    ) const noexcept -> bool {

        if ( this == & iterator ) {
            return true;
        }

        auto pObject = reinterpret_cast < decltype ( this ) > ( & iterator );
        return this->_pArray == pObject->_pArray && this->_index == pObject->_index;
    }


    template < typename __ElementType > // NOLINT(bugprone-reserved-identifier)
    __CDS_OptimalInline auto Array < __ElementType > :: ArrayDelegateConstIterator :: copy () const noexcept -> ArrayDelegateConstIterator * {

        return cds :: copy ( * this );
    }

}

#endif // __CDS_ARRAY_DELEGATE_CONST_ITERATOR_IMPL_HPP__
