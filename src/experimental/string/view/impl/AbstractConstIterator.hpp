//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_VIEW_BASE_ABSTRACT_CONST_ITERATOR_IMPL_HPP__
#define __CDS_EX_STRING_VIEW_BASE_ABSTRACT_CONST_ITERATOR_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
            namespace __impl { // NOLINT(bugprone-reserved-identifier)

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr __BaseStringView < __CharType > :: AbstractConstIterator :: AbstractConstIterator (
                        __BaseStringView < __CharType > const * pString,
                        Index                                   index,
                        bool                                    forward
                ) noexcept :
                        _pString ( pString ),
                        _index ( index ),
                        _forward ( forward ) {

                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr __BaseStringView < __CharType > :: AbstractConstIterator :: AbstractConstIterator (
                        AbstractConstIterator && iterator
                ) noexcept :
                        _pString ( exchange ( iterator._pString, nullptr ) ),
                        _index ( exchange ( iterator._index, 0 ) ),
                        _forward ( exchange ( iterator._forward, true ) ) {

                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: AbstractConstIterator :: operator = (
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

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: AbstractConstIterator :: operator = (
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

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                __CDS_cpplang_NonConstConstexprMemberFunction auto __BaseStringView < __CharType > :: AbstractConstIterator :: previous () noexcept -> AbstractConstIterator & {

                    this->_forward ? -- this->_index : ++ this->_index;
                    return * this;
                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __BaseStringView < __CharType > :: AbstractConstIterator :: value () const noexcept -> __CharType {

                    return this->_pString->_pBuffer [ this->_index ];
                }

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                constexpr auto __BaseStringView < __CharType > :: AbstractConstIterator :: equals (
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
