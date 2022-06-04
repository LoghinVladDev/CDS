//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_VIEW_BASE_ABSTRACT_CONST_ITERATOR_IMPL_HPP__
#define __CDS_EX_STRING_VIEW_BASE_ABSTRACT_CONST_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                constexpr BaseStringView < CharType > :: AbstractConstIterator :: AbstractConstIterator (
                        BaseStringView < CharType > const * pString,
                        Index                               index,
                        bool                                forward
                ) noexcept :
                        _pString ( pString ),
                        _index ( index ),
                        _forward ( forward ) {

                }

                template < typename CharType >
                constexpr BaseStringView < CharType > :: AbstractConstIterator :: AbstractConstIterator (
                        AbstractConstIterator && iterator
                ) noexcept :
                        _pString ( exchange ( iterator._pString, nullptr ) ),
                        _index ( exchange ( iterator._index, 0 ) ),
                        _forward ( exchange ( iterator._forward, true ) ) {

                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: AbstractConstIterator :: operator = (
                        AbstractConstIterator const & iterator
                ) noexcept -> AbstractConstIterator & {

                    if ( this == & iterator ) {
                        return * this;
                    }

                    this->_pString  = iterator._pString;
                    this->_index    = iterator._index;
                    this->_forward  = iterator._forward;

                    return * this;
                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: AbstractConstIterator :: operator = (
                        AbstractConstIterator && iterator
                ) noexcept -> AbstractConstIterator & {

                    if ( this == & iterator ) {
                        return * this;
                    }

                    this->_pString  = exchange ( iterator._pString, nullptr );
                    this->_index    = exchange ( iterator._index, 0 );
                    this->_forward  = exchange ( iterator._forward, true );

                    return * this;
                }

                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseStringView < CharType > :: AbstractConstIterator :: previous () noexcept -> AbstractConstIterator & {

                    this->_forward ? -- this->_index : ++ this->_index;
                    return * this;
                }

                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: AbstractConstIterator :: value () const noexcept -> CharType {

                    return this->_pString->_pBuffer [ this->_index ];
                }

                template < typename CharType >
                constexpr auto BaseStringView < CharType > :: AbstractConstIterator :: equals (
                        AbstractConstIterator const & iterator
                ) const noexcept -> bool {

                    return
                            this->_pString  == iterator._pString    &&
                            this->_index    == iterator._index      &&
                            this->_forward  == iterator._forward;
                }

            }
        }
    }
}

#endif // __CDS_EX_STRING_VIEW_BASE_ABSTRACT_CONST_ITERATOR_IMPL_HPP__
