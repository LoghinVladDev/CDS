//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_STRING_STRING_UTILS_HPP__
#define __CDS_STRING_STRING_UTILS_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)

    namespace __hidden { // NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            class __BaseStringView; // NOLINT(bugprone-reserved-identifier)

            template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
            class __BaseString; // NOLINT(bugprone-reserved-identifier)

        }
    }

    namespace meta { // NOLINT(modernize-concat-nested-namespaces)
        namespace __impl { // NOLINT(bugprone-reserved-identifier)

            template < typename >
            struct __IsStringCharType               : FalseType {}; // NOLINT(bugprone-reserved-identifier)

            template <>
            struct __IsStringCharType < char >      : TrueType {};

            template <>
            struct __IsStringCharType < wchar_t >   : TrueType {};


            template < typename __CharType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
            struct __IsIntegralToString : BoolConstant < // NOLINT(bugprone-reserved-identifier)
                    ! isSame < __CharType, __NumericType > () && (
                            isSigned    < __NumericType > () ||
                            isUnsigned  < __NumericType > ()
                    ) && isIntegral < __NumericType > ()
            > {};


            template < typename, typename, typename = void >
            struct __IsConvertibleToBaseStringView : FalseType {}; // NOLINT(bugprone-reserved-identifier)

            template < typename __ConvertibleType, typename __CharType > // NOLINT(bugprone-reserved-identifier)
            struct __IsConvertibleToBaseStringView < // NOLINT(bugprone-reserved-identifier)
                    __ConvertibleType,
                    __CharType,
                    Void < decltype ( __hidden :: __impl :: __BaseStringView < __CharType > ( valueOf < __ConvertibleType > () ) ) >
            > : BoolConstant <
                    ! meta :: isSame < __ConvertibleType, __hidden :: __impl :: __BaseStringView < __CharType > > () && (
                            meta :: isSame < Decay < __ConvertibleType >, __CharType const * > ()                                       ||
                            meta :: isSame < Decay < __ConvertibleType >, __CharType * > ()                                             ||
                            meta :: isSame < Decay < __ConvertibleType >, __hidden :: __impl :: __BaseString < __CharType > const > ()  ||
                            meta :: isSame < Decay < __ConvertibleType >, __hidden :: __impl :: __BaseString < __CharType > > ()        ||
                            meta :: isSame < Decay < __ConvertibleType >, std :: basic_string < __CharType > const > ()                 ||
                            meta :: isSame < Decay < __ConvertibleType >, std :: basic_string < __CharType > > ()
                    )
            > {};


            template < typename, typename, typename = void >
            struct __IsNonAmbiguousConvertibleToBaseStringView : FalseType {}; // NOLINT(bugprone-reserved-identifier)

            template < typename >
            struct __StringData {}; // NOLINT(bugprone-reserved-identifier)

            template <>
            struct __StringData < char > {
                constexpr static char       const * const emptyString       = "";
                constexpr static char               const nullCharacter     = '\0';
                constexpr static char       const * const digits            = "0123456789";
                constexpr static char       const * const lowercaseAlphabet = "abcdefghijklmnopqrstuvxyzw";
                constexpr static char       const * const uppercaseAlphabet = "ABCDEFGHIJKLMNOPQRSTUVXYZW";
                constexpr static char       const * const vowels            = "AEIOUaeiou";
                constexpr static char       const * const consonants        = "BCDFGHJKLMNPQRSTVXYZWbcdfghjklmnpqrstvxyzw";
            };

            template <>
            struct __StringData < wchar_t > {
                constexpr static wchar_t    const * const emptyString       = L"";
                constexpr static wchar_t            const nullCharacter     = L'\0';
                constexpr static wchar_t    const * const digits            = L"0123456789";
                constexpr static wchar_t    const * const lowercaseAlphabet = L"abcdefghijklmnopqrstuvxyzw";
                constexpr static wchar_t    const * const uppercaseAlphabet = L"ABCDEFGHIJKLMNOPQRSTUVXYZW";
                constexpr static wchar_t    const * const vowels            = L"AEIOUaeiou";
                constexpr static wchar_t    const * const consonants        = L"BCDFGHJKLMNPQRSTVXYZWbcdfghjklmnpqrstvxyzw";
            };
        }

        template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto isStringCharType () noexcept -> bool { // NOLINT(bugprone-reserved-identifier)
            return __impl :: __IsStringCharType < __CharType > :: value;
        }

        template < typename __CharType, typename __NumericType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto isIntegralToString () noexcept -> bool { // NOLINT(bugprone-reserved-identifier)
            return __impl :: __IsIntegralToString < __CharType, __NumericType > :: value;
        }

        template < typename __ConvertibleType, typename __CharType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto isConvertibleToBaseStringView () noexcept -> bool { // NOLINT(bugprone-reserved-identifier)
            return __impl :: __IsConvertibleToBaseStringView < __ConvertibleType, __CharType > :: value;
        }

        template < typename __ConvertibleType, typename __CharType > // NOLINT(bugprone-reserved-identifier)
        constexpr auto isNonAmbiguousConvertibleToBaseStringView () noexcept -> bool { // NOLINT(bugprone-reserved-identifier)
            return
                    isConvertibleToBaseStringView < __ConvertibleType, __CharType > () &&
                    ! isSame < Decay < __ConvertibleType >, __hidden :: __impl :: __BaseString < __CharType > > ();
        }
    }

    template < typename __CharType > // NOLINT(bugprone-reserved-identifier)
    class StringUtils {

    public:
        using ElementType = __CharType;

    public:
        StringUtils () noexcept = delete;

    public:
        static sint8 const lesser       { -1 };

    public:
        static sint8 const equal        {  0 };

    public:
        static sint8 const greater      {  1 };

    public:
        static Index const invalidIndex { -1 };

    public:
        constexpr static auto isUpper (
                ElementType character
        ) noexcept -> bool;

    public:
        constexpr static auto isLower (
                ElementType character
        ) noexcept -> bool;

    public:
        constexpr static auto isDigit (
                ElementType character
        ) noexcept -> bool;

    public:
        constexpr static auto isLetter (
                ElementType character
        ) noexcept -> bool;

    public:
        constexpr static auto isAlpha (
                ElementType character
        ) noexcept -> bool;

    public:
        constexpr static auto isVowel (
                ElementType character
        ) noexcept -> bool;

    public:
        constexpr static auto isConsonant (
                ElementType character
        ) noexcept -> bool;

    public:
        constexpr static auto lower (
                ElementType character
        ) noexcept -> ElementType;

    public:
        constexpr static auto upper (
                ElementType character
        ) noexcept -> ElementType;

    public:
        __CDS_cpplang_ConstexprConditioned static auto compare (
                ElementType const * pLeftBuffer,
                Size                leftLength,
                ElementType const * pRightBuffer,
                Size                rightLength
        ) noexcept -> sint8;

    public:
        __CDS_cpplang_ConstexprConditioned static auto length (
                ElementType const * pBuffer
        ) noexcept -> Size;

    public:
        __CDS_cpplang_ConstexprConditioned static auto copy (
                ElementType       * pDestination,
                Size                destinationOffset,
                ElementType const * pSource,
                Size                sourceOffset,
                Size                length,
                bool                writeTerminator = true
        ) noexcept -> ElementType *;

    public:
        template < typename __OtherCharType, meta :: EnableIf < ! meta :: isSame < __OtherCharType, __CharType > () && sizeof ( __CharType ) >= sizeof ( __OtherCharType ) > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned static auto copy (
                ElementType           * pDestination,
                Size                    destinationOffset,
                __OtherCharType const * pSource,
                Size                    sourceOffset,
                Size                    length,
                bool                    writeTerminator = true
        ) noexcept -> ElementType *;

    public:
        template < typename __NumericType, meta :: EnableIf < meta :: isUnsigned < __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned static auto integerLength (
                __NumericType value,
                uint8         base = 10U
        ) noexcept -> uint8;

    public:
        template < typename __NumericType, meta :: EnableIf < meta :: isSigned < __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned static auto integerLength (
                __NumericType value,
                uint8         base = 10U
        ) noexcept -> uint8;

    public:
        template < typename __NumericType, meta :: EnableIf < meta :: isUnsigned < __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned static auto writeInteger (
                ElementType           * pDestination,
                Size                    offset,
                __NumericType           value,
                uint8                   valueLength,
                Size                  * pOffsetAfterWrite
        ) noexcept -> ElementType *;

    public:
        template < typename __NumericType, meta :: EnableIf < meta :: isSigned < __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_cpplang_ConstexprConditioned static auto writeInteger (
                ElementType           * pDestination,
                Size                    offset,
                __NumericType           value,
                uint8                   valueLength,
                Size                  * pOffsetAfterWrite
        ) noexcept -> ElementType *;

    public:
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        static auto find (
                ElementType                 const * pSource,
                Size                                sourceLength,
                ElementType                 const * toBeFound,
                Size                                toBeFoundLength,
                Size                                maxCount,
                __CollectionType < Index >        & storeIn
        ) noexcept -> __CollectionType < Index > &;

    public:
        __CDS_cpplang_ConstexprDynamicAllocation static auto findFirst (
                ElementType     const * pSource,
                Size                    sourceLength,
                ElementType     const * toBeFound,
                Size                    toBeFoundLength
        ) noexcept -> Index;

    public:
        __CDS_cpplang_ConstexprDynamicAllocation static auto findLast (
                ElementType     const * pSource,
                Size                    sourceLength,
                ElementType     const * toBeFound,
                Size                    toBeFoundLength
        ) noexcept -> Index;

    public:
        template < template < typename ... > class __CollectionType > // NOLINT(bugprone-reserved-identifier)
        static auto findAll (
                ElementType                 const * pSource,
                Size                                sourceLength,
                ElementType                 const * toBeFound,
                Size                                toBeFoundLength,
                __CollectionType < Index >        & storeIn
        ) noexcept -> __CollectionType < Index > &;

    public:
        static auto findAll (
                ElementType                 const * pSource,
                Size                                sourceLength,
                ElementType                 const * toBeFound,
                Size                                toBeFoundLength,
                Index                             * pIndices,
                Size                                maxIndexCount
        ) noexcept -> Size;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto contains (
                ElementType const * pBuffer,
                Size                length,
                ElementType         character
        ) noexcept -> bool;

    public:
        template < typename __ArgumentType, meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ArgumentType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                __ArgumentType && argumentType
        ) noexcept -> Size;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                __hidden :: __impl :: __BaseStringView < __CharType > const & string
        ) noexcept -> Size;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                ElementType character
        ) noexcept -> Size;

    public:
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                bool value
        ) noexcept -> Size;

    public:
        template < typename __NumericType, meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                __NumericType value
        ) noexcept -> Size;

    public:
        template < typename __FloatingPointType, meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0 > // NOLINT(bugprone-reserved-identifier)
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                __FloatingPointType value
        ) noexcept -> Size;

    public:
        template < typename ... __ArgumentTypes > // NOLINT(bugprone-reserved-identifier)
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArguments (
                __ArgumentTypes && ... arguments
        ) noexcept -> Size;
    };

}

#endif // __CDS_STRING_STRING_UTILS_HPP__
