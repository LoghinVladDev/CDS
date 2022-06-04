//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_UTILS_IMPL_HPP__
#define __CDS_EX_STRING_UTILS_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        namespace hidden {
            namespace impl {

                template < typename NumericType, meta :: EnableIf < meta :: isUnsigned < NumericType > () > = 0 >
                __CDS_cpplang_ConstexprConditioned auto numberStringLength (
                        NumericType value,
                        uint8       base = 10U
                ) noexcept -> uint8 {

                    uint8 digitCount = 1U;
                    uint32 const base2 = base * base;
                    uint32 const base3 = base2 * base;
                    uint32 const base4 = base3 * base;

                    while ( true ) {

                        if ( value < base ) {
                            return digitCount;
                        } else if ( value < base2 ) {
                            return digitCount + 1U;
                        } else if ( value < base3 ) {
                            return digitCount + 2U;
                        } else {
                            /// nothing
                        }

                        value /= base4;
                        digitCount += 4U;
                    }
                }

            }
        }

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

            while ( * pBuffer != static_cast < ElementType > ( '\0' ) ) {
                ++ size;
                ++ pBuffer;
            }

            return size;
        }


        template < typename CharType >
        __CDS_cpplang_ConstexprConditioned auto StringUtils < CharType > :: copy (
                ElementType       * pDestination,
                ElementType const * pSource,
                Size                length
        ) noexcept -> ElementType * {

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

            (void) std :: memcpy (
                    pDestination,
                    pSource,
                    length * sizeof ( CharType )
            );

            pDestination [ length ] = static_cast < ElementType > ( '\0' );
            return pDestination;
        }


        template < typename CharType >
        template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > >
        __CDS_cpplang_ConstexprConditioned auto StringUtils < CharType > :: copy (
                ElementType         * pDestination,
                OtherCharType const * pSource,
                Size                  length
        ) noexcept -> ElementType * {

            if ( pDestination == nullptr || pSource == nullptr ) {
                return nullptr;
            }

            for ( Size index = 0U; index < length; ++ index ) {
                pDestination [ index ] = static_cast < ElementType > ( pSource [ index ] );
            }

            pDestination [ length ] = static_cast < ElementType > ( '\0' );
            return pDestination;
        }


        template < typename CharType >
        template < typename NumericType, meta :: EnableIf < meta :: isUnsigned < NumericType > () > >
        __CDS_cpplang_ConstexprConditioned auto StringUtils < CharType > :: write (
                ElementType   * pDestination,
                Size            offset,
                NumericType     value,
                Size          * pOffsetAfterWrite
        ) noexcept -> ElementType * {

            constexpr char numbersUntil100 [201] =
                    "0001020304050607080910111213141516171819"
                    "2021222324252627282930313233343536373839"
                    "4041424344454647484950515253545556575859"
                    "6061626364656667686970717273747576777879"
                    "8081828384858687888990919293949596979899";

            if ( pDestination == nullptr ) {
                return pDestination;
            }

            uint32 const numberLength = hidden :: impl :: numberStringLength ( value );
            uint32 reversedStartPos = offset + numberLength - 1U;
            while ( value >= 100U ) {

                auto const numberOffset = ( value % 100U ) * 2U;
                value /= 100U;

                pDestination [ reversedStartPos ]       = static_cast < ElementType > ( numbersUntil100 [ numberOffset + 1U ] );
                pDestination [ reversedStartPos - 1U ]  = static_cast < ElementType > ( numbersUntil100 [ numberOffset ] );

                reversedStartPos -= 2U;
            }

            if ( value >= 10U ) {

                auto const numberOffset = value * 2U;

                pDestination [ offset + 1U ]    = static_cast < ElementType > ( numbersUntil100 [ numberOffset + 1U ] );
                pDestination [ offset ]         = static_cast < ElementType > ( numbersUntil100 [ numberOffset ] );
            } else {

                pDestination [ offset ]         = static_cast < ElementType > ( '0' + value );
            }

            if ( pOffsetAfterWrite != nullptr ) {
                * pOffsetAfterWrite = offset + numberLength;
            }

            return pDestination + numberLength;
        }


        template < typename CharType >
        template < typename NumericType, meta :: EnableIf < meta :: isSigned < NumericType > () > >
        __CDS_cpplang_ConstexprConditioned auto StringUtils < CharType > :: write (
                ElementType   * pDestination,
                Size            offset,
                NumericType     value,
                Size          * pOffsetAfterWrite
        ) noexcept -> ElementType * {

            using UnsignedType = meta :: MakeUnsigned < NumericType >;

            bool const      isNegative      = value < 0;
            UnsignedType    unsignedValue   =
                    isNegative ? static_cast < UnsignedType > ( ~ value ) + 1U : static_cast < UnsignedType > ( value );

            if ( pDestination == nullptr ) {
                return pDestination;
            }

            if ( isNegative ) {
                pDestination [ offset ++ ] = '-';
            }

            return StringUtils :: write (
                    pDestination,
                    offset,
                    unsignedValue,
                    pOffsetAfterWrite
            );
        }

    }
}

#endif // __CDS_EX_STRING_UTILS_IMPL_HPP__
