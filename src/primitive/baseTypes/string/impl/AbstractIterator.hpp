//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_STRING_BASE_ABSTRACT_ITERATOR_IMPL_HPP__
#define __CDS_STRING_BASE_ABSTRACT_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseString < __CharType > :: AbstractIterator :: AbstractIterator (
                    __BaseString < __CharType >   * pString,
                    Index                           index,
                    bool                            forward
            ) noexcept :
                    _pString ( pString ),
                    _index ( index ),
                    _forward ( forward ) {

            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr __BaseString < __CharType > :: AbstractIterator :: AbstractIterator (
                    AbstractIterator && iterator
            ) noexcept :
                    _pString ( exchange ( iterator._pString, nullptr ) ),
                    _index ( exchange ( iterator._index, 0 ) ),
                    _forward ( exchange ( iterator._forward, true ) ) {

            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: AbstractIterator :: operator = (
                    AbstractIterator const & iterator
            ) noexcept -> AbstractIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pString  = iterator._pString;
                this->_index    = iterator._index;
                this->_forward  = iterator._forward;

                return * this;
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: AbstractIterator :: operator = (
                    AbstractIterator && iterator
            ) noexcept -> AbstractIterator & {

                if ( this == & iterator ) {
                    return * this;
                }

                this->_pString  = exchange ( iterator._pString, nullptr );
                this->_index    = exchange ( iterator._index, 0 );
                this->_forward  = exchange ( iterator._forward, true );

                return * this;
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: AbstractIterator :: next () noexcept -> AbstractIterator & {

                this->_forward ? ++ this->_index : -- this->_index;
                return * this;
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseString < __CharType > :: AbstractIterator :: previous () noexcept -> AbstractIterator & {

                this->_forward ? -- this->_index : ++ this->_index;
                return * this;
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseString < __CharType > :: AbstractIterator :: value () const noexcept -> __CharType & {

                return this->_pString->_pBuffer [ this->_index ];
            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            constexpr auto __BaseString < __CharType > :: AbstractIterator :: equals (
                    AbstractIterator const & iterator
            ) const noexcept -> bool {

                return
                        this->_pString  == iterator._pString    &&
                        this->_index    == iterator._index      &&
                        this->_forward  == iterator._forward;
            }

        }
    }
}

#endif // __CDS_STRING_BASE_ABSTRACT_ITERATOR_IMPL_HPP__