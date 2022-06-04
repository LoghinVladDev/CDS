//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_UTILS_IMPL_HPP__
#define __CDS_EX_STRING_UTILS_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename CharType >
        sint8 const StringUtils < CharType > :: lesser;

        template < typename CharType >
        sint8 const StringUtils < CharType > :: equal;

        template < typename CharType >
        sint8 const StringUtils < CharType > :: greater;


        template < typename CharType >
        constexpr auto StringUtils < CharType > :: isUpper (
                ElementType character
        ) noexcept -> bool {

            return
                character >= static_cast < ElementType > ( 'A' ) &&
                character <= static_cast < ElementType > ( 'Z' );
        }


        template < typename CharType >
        constexpr auto StringUtils < CharType > :: isLower (
                ElementType character
        ) noexcept -> bool {

            return
                character >= static_cast < ElementType > ( 'a' ) &&
                character <= static_cast < ElementType > ( 'z' );
        }


        template < typename CharType >
        constexpr auto StringUtils < CharType > :: isDigit (
                ElementType character
        ) noexcept -> bool {

            return
                character >= static_cast < ElementType > ( '0' ) &&
                character <= static_cast < ElementType > ( '9' );
        }


        template < typename CharType >
        constexpr auto StringUtils < CharType > :: isLetter (
                ElementType character
        ) noexcept -> bool {

            return
                    StringUtils :: isUpper ( character ) ||
                    StringUtils :: isLower ( character );
        }


        template < typename CharType >
        constexpr auto StringUtils < CharType > :: isAlpha (
                ElementType character
        ) noexcept -> bool {

            return
                    StringUtils :: isLetter ( character ) ||
                    StringUtils :: isDigit ( character );
        }


        template < typename CharType >
        constexpr auto StringUtils < CharType > :: isVowel (
                ElementType character
        ) noexcept -> bool {

            return
                    character == static_cast < ElementType > ( 'a' ) ||
                    character == static_cast < ElementType > ( 'e' ) ||
                    character == static_cast < ElementType > ( 'i' ) ||
                    character == static_cast < ElementType > ( 'o' ) ||
                    character == static_cast < ElementType > ( 'u' ) ||
                    character == static_cast < ElementType > ( 'A' ) ||
                    character == static_cast < ElementType > ( 'E' ) ||
                    character == static_cast < ElementType > ( 'I' ) ||
                    character == static_cast < ElementType > ( 'O' ) ||
                    character == static_cast < ElementType > ( 'U' );
        }


        template < typename CharType >
        constexpr auto StringUtils < CharType > :: isConsonant (
                ElementType character
        ) noexcept -> bool {

            return
                    StringUtils :: isLetter ( character ) &&
                    ! StringUtils :: isVowel ( character );
        }


        template < typename CharType >
        constexpr auto StringUtils < CharType > :: lower (
                ElementType character
        ) noexcept -> ElementType {

            if ( ! StringUtils :: isUpper ( character ) ) {
                return character;
            }

            return character - static_cast < ElementType > ( 'A' ) + static_cast < ElementType > ( 'a' );
        }


        template < typename CharType >
        constexpr auto StringUtils < CharType > :: upper (
                ElementType character
        ) noexcept -> ElementType {

            if ( ! StringUtils :: isLower ( character ) ) {
                return character;
            }

            return character - static_cast < ElementType > ( 'a' ) + static_cast < ElementType > ( 'A' );
        }


        template < typename CharType >
        __CDS_cpplang_ConstexprConditioned auto StringUtils < CharType > :: compare (
                ElementType const * pLeftString,
                Size                leftLength,
                ElementType const * pRightString,
                Size                rightLength
        ) noexcept -> sint8 {

            if ( pLeftString == nullptr && pRightString == nullptr ) {
                return StringUtils :: equal;
            }

            if ( pLeftString == nullptr ) {
                return StringUtils :: lesser;
            }

            if ( pRightString == nullptr ) {
                return StringUtils :: greater;
            }

            Size const length = minOf ( leftLength, rightLength );
            for ( Size index = 0ULL; index < length; ++ index ) {

                if ( pLeftString [ index ] < pRightString [ index ] ) {
                    return StringUtils :: lesser;
                }

                if ( pLeftString [ index ] > pRightString [ index ] ) {
                    return StringUtils :: greater;
                }
            }

            if ( leftLength < rightLength ) {
                return StringUtils :: lesser;
            }

            if ( leftLength > rightLength ) {
                return StringUtils :: greater;
            }

            return StringUtils :: equal;
        }


        template < typename CharType >
        __CDS_cpplang_ConstexprConditioned auto StringUtils < CharType > :: length (
                ElementType const * pBuffer
        ) noexcept -> Size {

            Size size = 0ULL;

            if ( pBuffer == nullptr ) {
                return size;
            }

            while ( * pBuffer != '\0' ) {
                ++ size;
                ++ pBuffer;
            }

            return size;
        }

    }
}

#endif // __CDS_EX_STRING_UTILS_IMPL_HPP__
