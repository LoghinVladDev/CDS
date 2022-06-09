//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_STRING_UTILS_IMPL_HPP__
#define __CDS_STRING_UTILS_IMPL_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            namespace __allocation { // NOLINT(bugprone-reserved-identifier)

                constexpr static Size const __minCapacity = 64ULL; // NOLINT(bugprone-reserved-identifier)

                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                inline auto __alloc ( // NOLINT(bugprone-reserved-identifier)
                        Size capacity
                ) noexcept -> __CharType * {

                    return reinterpret_cast < __CharType * > (
                            malloc ( capacity * sizeof ( __CharType ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                inline auto __realloc ( // NOLINT(bugprone-reserved-identifier)
                        __CharType  * pBuffer,
                        Size          newCapacity
                ) noexcept -> __CharType * {

                    return reinterpret_cast < __CharType * > (
                            realloc ( pBuffer, newCapacity * sizeof ( __CharType ) )
                    );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                inline auto __enlarge ( // NOLINT(bugprone-reserved-identifier)
                        __CharType  * pBuffer,
                        Size          oldCapacity,
                        Size          newCapacity,
                        Size        * pStoreNewCapacity
                ) noexcept -> __CharType * {

                    if ( oldCapacity >= newCapacity ) {
                        return pBuffer;
                    }

                    if ( newCapacity < __minCapacity ) {
                        newCapacity = __minCapacity;
                    }

                    * pStoreNewCapacity = newCapacity;
                    return __realloc ( pBuffer, newCapacity );
                }


                template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
                inline auto __free ( // NOLINT(bugprone-reserved-identifier)
                        __CharType * pBuffer
                ) noexcept -> void {

                    free ( pBuffer );
                }

            }

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            __CDS_cpplang_ConstexprConditioned auto __KMPComputeLPSArray ( // NOLINT(bugprone-reserved-identifier)
                    __CharType  const * pPatternString,
                    Size                length,
                    Index             * pLPSArray
            ) noexcept -> void {

                Index parseIndex    = 0ULL;

                Size lpsArrayIndex  = 1ULL;
                pLPSArray [0]       = 0;

                while ( lpsArrayIndex < length ) {

                    if ( pPatternString [ lpsArrayIndex ] == pPatternString [ parseIndex ] ) {
                        pLPSArray [ lpsArrayIndex ++ ] = ++ parseIndex;
                    } else {

                        if ( parseIndex > 0 ) {
                            parseIndex = pLPSArray [ parseIndex - 1 ];
                        } else {
                            pLPSArray [ lpsArrayIndex ++ ] = 0;
                        }
                    }
                }
            }

            template < typename __CharType, typename __ArgumentType > // NOLINT(bugprone-reserved-identifier)
            __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __stringLengthOfArguments (  // NOLINT(bugprone-reserved-identifier)
                    __ArgumentType && argument
            ) noexcept -> Size {

                return StringUtils < __CharType > :: stringLengthOfArgument (
                        std :: forward < __ArgumentType > ( argument )
                );
            }

            template < typename __CharType, typename __FirstArgumentType, typename ... __RemainingArgumentTypes > // NOLINT(bugprone-reserved-identifier)
            __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto __stringLengthOfArguments (  // NOLINT(bugprone-reserved-identifier)
                    __FirstArgumentType      &&     firstArgument,
                    __RemainingArgumentTypes && ... remainingArguments
            ) noexcept -> Size {

                return StringUtils < __CharType > :: stringLengthOfArgument (
                        std :: forward < __FirstArgumentType > ( firstArgument )
                ) + __stringLengthOfArguments < __CharType, __RemainingArgumentTypes ... > (
                        std :: forward < __RemainingArgumentTypes > ( remainingArguments ) ...
                );
            }

        }
    }

    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    sint8 const StringUtils < __CharType > :: lesser;

    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    sint8 const StringUtils < __CharType > :: equal;

    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    sint8 const StringUtils < __CharType > :: greater;

    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    Index const StringUtils < __CharType > :: invalidIndex;


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto StringUtils < __CharType > :: isUpper (
            ElementType character
    ) noexcept -> bool {

        return
            character >= static_cast < ElementType > ( 'A' ) &&
            character <= static_cast < ElementType > ( 'Z' );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto StringUtils < __CharType > :: isLower (
            ElementType character
    ) noexcept -> bool {

        return
            character >= static_cast < ElementType > ( 'a' ) &&
            character <= static_cast < ElementType > ( 'z' );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto StringUtils < __CharType > :: isDigit (
            ElementType character
    ) noexcept -> bool {

        return
            character >= static_cast < ElementType > ( '0' ) &&
            character <= static_cast < ElementType > ( '9' );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto StringUtils < __CharType > :: isLetter (
            ElementType character
    ) noexcept -> bool {

        return
                StringUtils :: isUpper ( character ) ||
                StringUtils :: isLower ( character );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto StringUtils < __CharType > :: isAlpha (
            ElementType character
    ) noexcept -> bool {

        return
                StringUtils :: isLetter ( character ) ||
                StringUtils :: isDigit ( character );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto StringUtils < __CharType > :: isVowel (
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


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto StringUtils < __CharType > :: isConsonant (
            ElementType character
    ) noexcept -> bool {

        return
                StringUtils :: isLetter ( character ) &&
                ! StringUtils :: isVowel ( character );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto StringUtils < __CharType > :: lower (
            ElementType character
    ) noexcept -> ElementType {

        return
                ! StringUtils :: isUpper ( character ) ?
                character :
                character - static_cast < ElementType > ( 'A' ) + static_cast < ElementType > ( 'a' );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    constexpr auto StringUtils < __CharType > :: upper (
            ElementType character
    ) noexcept -> ElementType {

        return
                ! StringUtils :: isLower ( character ) ?
                character :
                character - static_cast < ElementType > ( 'a' ) + static_cast < ElementType > ( 'A' );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: compare (
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


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: length (
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


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: copy (
            ElementType       * pDestination,
            Size                destinationOffset,
            ElementType const * pSource,
            Size                sourceOffset,
            Size                length,
            bool                writeTerminator
    ) noexcept -> ElementType * {

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

        (void) std :: memcpy (
                pDestination + destinationOffset,
                pSource + sourceOffset,
                length * sizeof ( __CharType )
        );

        if ( writeTerminator ) {
            pDestination [ destinationOffset + length ] = static_cast < ElementType > ( '\0' );
        }

        return pDestination;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < typename __OtherCharType, meta :: EnableIf < ! meta :: isSame < __OtherCharType, __CharType > () && sizeof ( __CharType ) >= sizeof ( __OtherCharType ) > > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: copy (
            ElementType           * pDestination,
            Size                    destinationOffset,
            __OtherCharType const * pSource,
            Size                    sourceOffset,
            Size                    length,
            bool                    writeTerminator
    ) noexcept -> ElementType * {

        if ( pDestination == nullptr || pSource == nullptr ) {
            return nullptr;
        }

        for ( Size index = 0U; index < length; ++ index ) {
            pDestination [ destinationOffset + index ] = static_cast < ElementType > ( pSource [ sourceOffset + index ] );
        }

        if ( writeTerminator ) {
            pDestination [ destinationOffset + length ] = static_cast < ElementType > ( '\0' );
        }

        return pDestination;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < typename __NumericType, meta :: EnableIf < meta :: isUnsigned < __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: integerLength (
            __NumericType value,
            uint8         base
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
            } else if ( value < base4 ) {
                return digitCount + 3U;
            } else {
                /// nothing
            }

            value /= base4;
            digitCount += 4U;
        }
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < typename __NumericType, meta :: EnableIf < meta :: isSigned < __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: integerLength (
            __NumericType value,
            uint8         base
    ) noexcept -> uint8 {

        using               UnsignedType    = meta :: MakeUnsigned < __NumericType >;
        bool const          isNegative      = value < 0;

        return
                static_cast < uint8 > ( isNegative ) +
                StringUtils :: integerLength (
                        isNegative ? static_cast < UnsignedType > ( ~ value ) + 1U : static_cast < UnsignedType > ( value ),
                        base
                );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < typename __NumericType, meta :: EnableIf < meta :: isUnsigned < __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: writeInteger (
            ElementType   * pDestination,
            Size            offset,
            __NumericType   value,
            uint8           valueLength,
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

        uint32 reversedStartPos = static_cast < uint32 > ( offset ) + valueLength - 1U;
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
            * pOffsetAfterWrite = offset + valueLength;
        }

        return pDestination + offset + valueLength;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < typename __NumericType, meta :: EnableIf < meta :: isSigned < __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: writeInteger (
            ElementType   * pDestination,
            Size            offset,
            __NumericType   value,
            uint8           valueLength,
            Size          * pOffsetAfterWrite
    ) noexcept -> ElementType * {

        using UnsignedType = meta :: MakeUnsigned < __NumericType >;

        bool const          isNegative      = value < 0;
        UnsignedType const  unsignedValue   =
                isNegative ? static_cast < UnsignedType > ( ~ value ) + 1U : static_cast < UnsignedType > ( value );

        if ( pDestination == nullptr ) {
            return pDestination;
        }

        if ( isNegative ) {
            pDestination [ offset ++ ] = '-';
        }

        return StringUtils :: writeInteger (
                pDestination,
                offset,
                unsignedValue,
                valueLength - static_cast < uint8 > ( isNegative ),
                pOffsetAfterWrite
        );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    inline auto StringUtils < __CharType > :: find (
            ElementType                 const * pSource,
            Size                                sourceLength,
            ElementType                 const * pToBeFound,
            Size                                toBeFoundLength,
            Size                                maxCount,
            __CollectionType < Index >        & storeIn
    ) noexcept -> __CollectionType < Index > & {

        auto pLPSArray = __hidden :: __impl :: __allocation :: __alloc < Index > ( toBeFoundLength );

        __hidden :: __impl :: __KMPComputeLPSArray (
                pToBeFound,
                toBeFoundLength,
                pLPSArray
        );

        Index sourceIndex   = 0;
        Index patternIndex  = 0;
        Size  found         = 0ULL;

        while ( sourceIndex < static_cast < Index > ( sourceLength ) ) {

            if ( pToBeFound [ patternIndex ] == pSource [ sourceIndex ] ) {

                ++ patternIndex;
                ++ sourceIndex;
            }

            if ( patternIndex == static_cast < Index > ( toBeFoundLength ) ) {

                if ( found < maxCount ) {
                    storeIn.add ( sourceIndex - patternIndex );
                    ++ found;
                } else {
                    __hidden :: __impl :: __allocation :: __free ( pLPSArray );
                    return storeIn;
                }
            } else if (
                    sourceIndex < static_cast < Index > ( sourceLength ) &&
                    pSource [ sourceIndex ] != pToBeFound [ patternIndex ]
            ) {

                if ( patternIndex != 0 ) {
                    patternIndex = pLPSArray [ patternIndex - 1 ];
                } else {
                    ++ sourceIndex;
                }
            } else {
                /// do nothing
            }
        }

        __hidden :: __impl :: __allocation :: __free ( pLPSArray );
        return storeIn;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprDynamicAllocation auto StringUtils < __CharType > :: findFirst (
            ElementType const * pSource,
            Size                sourceLength,
            ElementType const * pToBeFound,
            Size                toBeFoundLength
    ) noexcept -> Index {

        auto pLPSArray = __hidden :: __impl :: __allocation :: __alloc < Index > ( toBeFoundLength );

        __hidden :: __impl :: __KMPComputeLPSArray (
                pToBeFound,
                toBeFoundLength,
                pLPSArray
        );

        Index sourceIndex   = 0;
        Index patternIndex  = 0;

        while ( sourceIndex < static_cast < Index > ( sourceLength ) ) {

            if ( pToBeFound [ patternIndex ] == pSource [ sourceIndex ] ) {

                ++ patternIndex;
                ++ sourceIndex;
            }

            if ( patternIndex == static_cast < Index > ( toBeFoundLength ) ) {

                Index found = sourceIndex - patternIndex;
                __hidden :: __impl :: __allocation :: __free ( pLPSArray );
                return found;
            } else if (
                    sourceIndex < static_cast < Index > ( sourceLength ) &&
                    pSource [ sourceIndex ] != pToBeFound [ patternIndex ]
            ) {

                if ( patternIndex != 0 ) {
                    patternIndex = pLPSArray [ patternIndex - 1 ];
                } else {
                    ++ sourceIndex;
                }
            } else {
                /// do nothing
            }
        }

        __hidden :: __impl :: __allocation :: __free ( pLPSArray );
        return StringUtils :: invalidIndex;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprDynamicAllocation auto StringUtils < __CharType > :: findLast (
            ElementType const * pSource,
            Size                sourceLength,
            ElementType const * pToBeFound,
            Size                toBeFoundLength
    ) noexcept -> Index {

        auto pLPSArray = __hidden :: __impl :: __allocation :: __alloc < Index > ( toBeFoundLength );

        __hidden :: __impl :: __KMPComputeLPSArray (
                pToBeFound,
                toBeFoundLength,
                pLPSArray
        );

        Index sourceIndex   = 0;
        Index patternIndex  = 0;
        Index lastMatch     = StringUtils :: invalidIndex;

        while ( sourceIndex < static_cast < Index > ( sourceLength ) ) {

            if ( pToBeFound [ patternIndex ] == pSource [ sourceIndex ] ) {

                ++ patternIndex;
                ++ sourceIndex;
            }

            if ( patternIndex == static_cast < Index > ( toBeFoundLength ) ) {

                lastMatch = sourceIndex - patternIndex;
                patternIndex = pLPSArray [ patternIndex - 1 ];
            } else if (
                    sourceIndex < static_cast < Index > ( sourceLength ) &&
                    pSource [ sourceIndex ] != pToBeFound [ patternIndex ]
            ) {

                if ( patternIndex > 0 ) {
                    patternIndex = pLPSArray [ patternIndex - 1 ];
                } else {
                    ++ sourceIndex;
                }
            } else {
                /// do nothing
            }
        }

        __hidden :: __impl :: __allocation :: __free ( pLPSArray );
        return lastMatch;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
    inline auto StringUtils < __CharType > :: findAll (
            ElementType                 const * pSource,
            Size                                sourceLength,
            ElementType                 const * pToBeFound,
            Size                                toBeFoundLength,
            __CollectionType < Index >        & storeIn
    ) noexcept -> __CollectionType < Index > & {

        auto pLPSArray = __hidden :: __impl :: __allocation :: __alloc < Index > ( toBeFoundLength );

        __hidden :: __impl :: __KMPComputeLPSArray (
                pToBeFound,
                toBeFoundLength,
                pLPSArray
        );

        Index sourceIndex   = 0;
        Index patternIndex  = 0;

        while ( sourceIndex < static_cast < Index > ( sourceLength ) ) {

            if ( pToBeFound [ patternIndex ] == pSource [ sourceIndex ] ) {

                ++ patternIndex;
                ++ sourceIndex;
            }

            if ( patternIndex == static_cast < Index > ( toBeFoundLength ) ) {

                storeIn.add ( sourceIndex - patternIndex );
                patternIndex = pLPSArray [ patternIndex - 1 ];
            } else if (
                    sourceIndex < static_cast < Index > ( sourceLength ) &&
                    pSource [ sourceIndex ] != pToBeFound [ patternIndex ]
            ) {

                if ( patternIndex != 0 ) {
                    patternIndex = pLPSArray [ patternIndex - 1 ];
                } else {
                    ++ sourceIndex;
                }
            } else {
                /// do nothing
            }
        }

        __hidden :: __impl :: __allocation :: __free ( pLPSArray );
        return storeIn;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    inline auto StringUtils < __CharType > :: findAll (
            ElementType                 const * pSource,
            Size                                sourceLength,
            ElementType                 const * pToBeFound,
            Size                                toBeFoundLength,
            Index                             * pIndices,
            Size                                maxIndexCount
    ) noexcept -> Size {

        auto pLPSArray = __hidden :: __impl :: __allocation :: __alloc < Index > ( toBeFoundLength );

        __hidden :: __impl :: __KMPComputeLPSArray (
                pToBeFound,
                toBeFoundLength,
                pLPSArray
        );

        Index sourceIndex   = 0;
        Index patternIndex  = 0;
        Size indexCount     = 0ULL;

        while ( sourceIndex < static_cast < Index > ( sourceLength ) ) {

            if ( pToBeFound [ patternIndex ] == pSource [ sourceIndex ] ) {

                ++ patternIndex;
                ++ sourceIndex;
            }

            if ( patternIndex == static_cast < Index > ( toBeFoundLength ) ) {

                if ( indexCount < maxIndexCount ) {
                    pIndices [ indexCount ++ ] = sourceIndex - patternIndex;
                } else {
                    __hidden :: __impl :: __allocation :: __free ( pLPSArray );
                    return maxIndexCount;
                }

                patternIndex = pLPSArray [ patternIndex - 1 ];
            } else if (
                    sourceIndex < static_cast < Index > ( sourceLength ) &&
                    pSource [ sourceIndex ] != pToBeFound [ patternIndex ]
                    ) {

                if ( patternIndex != 0 ) {
                    patternIndex = pLPSArray [ patternIndex - 1 ];
                } else {
                    ++ sourceIndex;
                }
            } else {
                /// do nothing
            }
        }

        __hidden :: __impl :: __allocation :: __free ( pLPSArray );
        return indexCount;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: contains (
            ElementType const * pBuffer,
            Size                length,
            ElementType         character
    ) noexcept -> bool {

        for ( Size index = 0ULL; index < length; ++ index ) {
            if ( pBuffer [ index ] == character ) {
                return true;
            }
        }

        return false;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < typename __ArgumentType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ArgumentType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: stringLengthOfArgument (
            __ArgumentType && argumentType
    ) noexcept -> Size {

        return StringUtils < __CharType > :: stringLengthOfArgument (
                __hidden :: __impl :: __BaseStringView < __CharType > ( std :: forward < __ArgumentType > ( argumentType ) )
        );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: stringLengthOfArgument (
            __hidden :: __impl :: __BaseStringView < __CharType > const & string
    ) noexcept -> Size {

        return string.length();
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: stringLengthOfArgument (
            ElementType character
    ) noexcept -> Size {

        return 1ULL;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: stringLengthOfArgument (
            bool value
    ) noexcept -> Size {

        return value ? 4ULL : 5ULL;
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: stringLengthOfArgument (
            __NumericType value
    ) noexcept -> Size {

        return StringUtils < __CharType > :: integerLength ( value );
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > > // NOLINT(bugprone-reserved-identifier)
    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: stringLengthOfArgument (
            __FloatingPointType value
    ) noexcept -> Size {

        return 64ULL; /// leave constant for now, undeterministic way to constexpr determine length of float / double / long double
    }


    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
    __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned auto StringUtils < __CharType > :: stringLengthOfArguments (
            __ArgumentTypes && ... arguments
    ) noexcept -> Size {

        return __hidden :: __impl :: __stringLengthOfArguments < __CharType > (
                std :: forward < __ArgumentTypes > ( arguments ) ...
        );
    }
}

#endif // __CDS_STRING_UTILS_IMPL_HPP__
