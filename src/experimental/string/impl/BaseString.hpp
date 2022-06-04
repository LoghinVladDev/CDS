//
// Created by loghin on 6/3/22.
//

#ifndef __CDS_EX_STRING_BASE_IMPL_HPP__
#define __CDS_EX_STRING_BASE_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental { // NOLINT(modernize-concat-nested-namespaces)
        namespace hidden { // NOLINT(modernize-concat-nested-namespaces)
            namespace impl {

                template < typename CharType >
                constexpr BaseString < CharType > :: BaseString (
                        BaseString && string
                ) noexcept :
                        _pBuffer ( cds :: exchange ( string._pBuffer, nullptr ) ),
                        _length ( cds :: exchange ( string._length, 0ULL ) ),
                        _capacity ( cds :: exchange ( string._capacity, 0ULL ) ) {

                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: size () const noexcept -> Size {
                    return this->_length;
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: length () const noexcept -> Size {
                    return this->size();
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: capacity () const noexcept -> Size {
                    return this->_capacity;
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: empty () const noexcept -> bool {
                    return this->_length == 0ULL;
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: operator [] (
                        Index index
                ) noexcept (false) -> ElementType & {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator [] (
                        Index index
                ) const noexcept (false) -> ElementType {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: at (
                        Index index
                ) noexcept (false) -> ElementType & {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: at (
                        Index index
                ) const noexcept (false) -> ElementType {

                    return this->get ( index );
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: get (
                        Index index
                ) noexcept (false) -> ElementType & {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( index, 0 );
                    }


                    if ( index < 0 ) {
                        index += ( ( -index ) / static_cast < Index > ( this->size() ) + 1) *
                                static_cast < Index > ( this->size() );
                    }

                    if ( index >= static_cast < Index > ( this->size() ) ) {
                        index = index % static_cast < Index > ( this->size() );
                    }

                    return this->_pBuffer [ index ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: get (
                        Index index
                ) const noexcept (false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( index, 0 );
                    }


                    if ( index < 0 ) {
                        index += ( ( -index ) / static_cast < Index > ( this->size() ) + 1) *
                                static_cast < Index > ( this->size() );
                    }

                    if ( index >= static_cast < Index > ( this->size() ) ) {
                        index = index % static_cast < Index > ( this->size() );
                    }

                    return this->_pBuffer [ index ];
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: front () noexcept (false) -> ElementType & {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ 0 ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: front () const noexcept (false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ 0 ];
                }


                template < typename CharType >
                __CDS_cpplang_NonConstConstexprMemberFunction auto BaseString < CharType > :: back () noexcept(false) -> ElementType & {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ this->_length - 1U ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: back () const noexcept(false) -> ElementType {

                    if ( this->empty() ) {
                        throw OutOfBoundsException ( 0, 0 );
                    }

                    return this->_pBuffer [ this->_length - 1U ];
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        BaseString const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.c_str(),
                            string.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        ElementType const * pString
                ) const noexcept -> bool {

                    auto otherStringLength = StringUtils < CharType > :: length ( pString );
                    if ( this->length() != otherStringLength ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            pString,
                            otherStringLength
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator == (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->length() != 1ULL ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            & character,
                            1U
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    auto leftLength = StringUtils < CharType > :: length ( pLeftString );
                    if ( leftLength != rightString.length() ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            pLeftString,
                            leftLength,
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator == (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return false;
                    }

                    return StringUtils < CharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        BaseString const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    if ( this->length() != string.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.c_str(),
                            string.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        ElementType const * pString
                ) const noexcept -> bool {

                    auto otherStringLength = StringUtils < CharType > :: length ( pString );
                    if ( this->length() != otherStringLength ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            pString,
                            otherStringLength
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator != (
                        ElementType character
                ) const noexcept -> bool {

                    if ( this->_length != 1ULL ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            & character,
                            1U
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    if ( leftString.length() != rightString.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    auto leftLength = StringUtils < CharType > :: length ( pLeftString );
                    if ( leftLength != rightString.length() ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            pLeftString,
                            leftLength,
                            rightString.cStr(),
                            rightString.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator != (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    if ( string.length() != 1ULL ) {
                        return true;
                    }

                    return StringUtils < CharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) != StringUtils < CharType > :: equal;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        BaseString const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.c_str(),
                            string.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            pString,
                            StringUtils < CharType > :: length ( pString )
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator < (
                        ElementType character
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            & character,
                            1U
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            pLeftString,
                            StringUtils < CharType > :: length ( pLeftString ),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator < (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: lesser;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        BaseString const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            string.c_str(),
                            string.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        ElementType const * pString
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            pString,
                            StringUtils < CharType > :: length ( pString )
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator > (
                        ElementType character
                ) const noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            this->cStr(),
                            this->length(),
                            & character,
                            1U
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            leftString.cStr(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            leftString.c_str(),
                            leftString.length(),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            pLeftString,
                            StringUtils < CharType > :: length ( pLeftString ),
                            rightString.cStr(),
                            rightString.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator > (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    return StringUtils < CharType > :: compare (
                            & character,
                            1U,
                            string.cStr(),
                            string.length()
                    ) == StringUtils < CharType > :: greater;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        BaseString const & string
                ) const noexcept -> bool {

                    return ! this->operator > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator > ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        ElementType const * pString
                ) const noexcept -> bool {


                    return ! this->operator > ( pString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator <= (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->operator > ( character );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    return ! ( leftString > rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( leftString > rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( pLeftString > rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator <= (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    return ! ( character > string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        BaseString const & string
                ) const noexcept -> bool {

                    return ! this->operator < ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        BaseStringView < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator < ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        std :: basic_string < CharType > const & string
                ) const noexcept -> bool {

                    return ! this->operator < ( string );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        ElementType const * pString
                ) const noexcept -> bool {


                    return ! this->operator < ( pString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto BaseString < CharType > :: operator >= (
                        ElementType character
                ) const noexcept -> bool {

                    return ! this->operator < ( character );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        BaseStringView < CharType > const & leftString,
                        BaseString < CharType >     const & rightString
                ) noexcept -> bool {

                    return ! ( leftString < rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        std :: basic_string < CharType >    const & leftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( leftString < rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        CharType                            const * pLeftString,
                        BaseString < CharType >             const & rightString
                ) noexcept -> bool {

                    return ! ( pLeftString < rightString );
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprConditioned auto operator >= (
                        CharType                                    character,
                        BaseString < CharType >             const & string
                ) noexcept -> bool {

                    return ! ( character < string );
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: cStr () const noexcept -> ElementType const * {
                    return this->_pBuffer;
                }


                template < typename CharType >
                constexpr auto BaseString < CharType > :: data () noexcept -> ElementType * {
                    return this->_pBuffer;
                }


                template < typename CharType >
                __CDS_cpplang_ConstexprOverride auto BaseString < CharType > :: hash () const noexcept -> Index {
                    return static_cast < Index > ( this->_length );
                }


                template < typename CharType >
                template < typename Action >
                auto BaseString < CharType > :: forEach (
                        Action const & action
                ) const noexcept ( noexcept ( action ( meta :: valueOf < ElementType > () ) ) ) -> void {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        action ( this->_pBuffer [ index ] );
                    }
                }


                template < typename CharType >
                template < typename Action >
                auto BaseString < CharType > :: forEach (
                        Action const & action
                ) noexcept ( noexcept ( action ( meta :: referenceOf < ElementType > () ) ) ) -> void {

                    for ( Size index = 0ULL; index < this->_length; ++ index ) {
                        action ( this->_pBuffer [ index ] );
                    }
                }

            }
        }
    }
}

#endif // __CDS_EX_STRING_BASE_IMPL_HPP__
