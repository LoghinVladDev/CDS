/*
 * Created by loghin on 6/4/22.
 */

#ifndef __CDS_STRING_STRING_UTILS_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_STRING_STRING_UTILS_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

namespace cds {

    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __CharType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __BaseStringView;             /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            
            template < typename __CharType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            class __BaseString;                 /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

        } /* namespace __impl */
    } /* namespace __hidden */

    namespace meta {        /* NOLINT(modernize-concat-nested-namespaces) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename >
            struct __IsStringCharType               : FalseType {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */


            template <>
            struct __IsStringCharType < char >      : TrueType {};


            template <>
            struct __IsStringCharType < wchar_t >   : TrueType {};


            template < typename __CharType, typename __NumericType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsIntegralToString : BoolConstant <                /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    ! isSame < __CharType, __NumericType > () && (
                            isSigned    < __NumericType > () ||
                            isUnsigned  < __NumericType > ()
                    ) && isIntegral < __NumericType > ()
            > {};


            template < typename, typename, typename = void >
            struct __IsConvertibleToBaseStringView : FalseType {};  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template < typename __ConvertibleType, typename __CharType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
            struct __IsConvertibleToBaseStringView <                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __ConvertibleType,
                    __CharType,
                    cds :: meta :: Void < decltype ( __hidden :: __impl :: __BaseStringView < __CharType > ( valueOf < __ConvertibleType > () ) ) >
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

            template < typename >
            struct __StringData {}; /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            template <>
            struct __StringData < char > {
                constexpr static char       const * const emptyString       = "";
                constexpr static char               const nullCharacter     = '\0';
                constexpr static char       const * const digits            = "0123456789";
                constexpr static char       const * const lowercaseAlphabet = "abcdefghijklmnopqrstuvxyzw";
                constexpr static char       const * const uppercaseAlphabet = "ABCDEFGHIJKLMNOPQRSTUVXYZW";
                constexpr static char       const * const vowels            = "AEIOUaeiou";
                constexpr static char       const * const consonants        = "BCDFGHJKLMNPQRSTVXYZWbcdfghjklmnpqrstvxyzw";
                constexpr static char       const * const whitespace        = " \t\n\r\f";
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
                constexpr static wchar_t    const * const whitespace        = L" \t\n\r\f";
            };

        } /* namespace __impl */

        template < typename __CharType >                        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isStringCharType () noexcept -> bool {   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            return __impl :: __IsStringCharType < __CharType > :: value;
        }

        template < typename __CharType, typename __NumericType >    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isIntegralToString () noexcept -> bool {     /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            return __impl :: __IsIntegralToString < __CharType, __NumericType > :: value;
        }

        template < typename __ConvertibleType, typename __CharType >        /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isConvertibleToBaseStringView () noexcept -> bool {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            return __impl :: __IsConvertibleToBaseStringView < __ConvertibleType, __CharType > :: value;
        }

        template < typename __ConvertibleType, typename __CharType >                    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        constexpr auto isNonAmbiguousConvertibleToBaseStringView () noexcept -> bool {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            return
                    isConvertibleToBaseStringView < __ConvertibleType, __CharType > () &&
                    ! isSame < Decay < __ConvertibleType >, __hidden :: __impl :: __BaseString < __CharType > > ();
        }

    } /* namespace meta */

    template < typename __CharType > /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
    class StringUtils {

    public: /* NOLINT(readability-redundant-access-specifiers) */
        using ElementType = __CharType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        StringUtils () noexcept = delete;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        static sint8 const lesser       { -1 };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        static sint8 const equal        {  0 };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        static sint8 const greater      {  1 };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        static Index const invalidIndex { -1 };

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr static auto isUpper (
                ElementType character
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr static auto isLower (
                ElementType character
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr static auto isDigit (
                ElementType character
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr static auto isLetter (
                ElementType character
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr static auto isAlpha (
                ElementType character
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr static auto isVowel (
                ElementType character
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr static auto isConsonant (
                ElementType character
        ) noexcept -> bool;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr static auto lower (
                ElementType character
        ) noexcept -> ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        constexpr static auto upper (
                ElementType character
        ) noexcept -> ElementType;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConditioned static auto compare (
                ElementType const * pLeftBuffer,
                Size                leftLength,
                ElementType const * pRightBuffer,
                Size                rightLength
        ) noexcept -> sint8;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConditioned static auto length (
                ElementType const * pBuffer
        ) noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprConditioned static auto copy (
                ElementType       * pDestination,
                Size                destinationOffset,
                ElementType const * pSource,
                Size                sourceOffset,
                Size                length,
                bool                writeTerminator = true
        ) noexcept -> ElementType *;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __OtherCharType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf <
                        ! meta :: isSame < __OtherCharType, __CharType > () &&
                        sizeof ( __CharType ) >= sizeof ( __OtherCharType )
                > = 0
        > __CDS_cpplang_ConstexprConditioned static auto copy (
                ElementType           * pDestination,
                Size                    destinationOffset,
                __OtherCharType const * pSource,
                Size                    sourceOffset,
                Size                    length,
                bool                    writeTerminator = true
        ) noexcept -> ElementType *;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __NumericType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: isUnsigned < __NumericType > () > = 0
        > __CDS_cpplang_ConstexprConditioned static auto integerLength (
                __NumericType value,
                uint8         base = 10U
        ) noexcept -> uint8;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __NumericType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: isSigned < __NumericType > () > = 0
        > __CDS_cpplang_ConstexprConditioned static auto integerLength (
                __NumericType value,
                uint8         base = 10U
        ) noexcept -> uint8;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __NumericType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: isUnsigned < __NumericType > () > = 0
        > __CDS_cpplang_ConstexprConditioned static auto writeInteger (
                ElementType           * pDestination,
                Size                    offset,
                __NumericType           value,
                uint8                   valueLength,
                Size                  * pOffsetAfterWrite
        ) noexcept -> ElementType *;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __NumericType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: isSigned < __NumericType > () > = 0
        > __CDS_cpplang_ConstexprConditioned static auto writeInteger (
                ElementType           * pDestination,
                Size                    offset,
                __NumericType           value,
                uint8                   valueLength,
                Size                  * pOffsetAfterWrite
        ) noexcept -> ElementType *;

    public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
        template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        static auto find (
                ElementType                 const * pSource,
                Size                                sourceLength,
                ElementType                 const * toBeFound,
                Size                                toBeFoundLength,
                Size                                maxCount,
                __CollectionType < Index >        & storeIn
        ) noexcept -> __CollectionType < Index > &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDynamicAllocation static auto findFirst (
                ElementType     const * pSource,
                Size                    sourceLength,
                ElementType     const * toBeFound,
                Size                    toBeFoundLength
        ) noexcept -> Index;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_cpplang_ConstexprDynamicAllocation static auto findLast (
                ElementType     const * pSource,
                Size                    sourceLength,
                ElementType     const * toBeFound,
                Size                    toBeFoundLength
        ) noexcept -> Index;

    public:                                                             /* NOLINT(readability-redundant-access-specifiers) */
        template < template < typename ... > class __CollectionType >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        static auto findAll (
                ElementType                 const * pSource,
                Size                                sourceLength,
                ElementType                 const * toBeFound,
                Size                                toBeFoundLength,
                __CollectionType < Index >        & storeIn
        ) noexcept -> __CollectionType < Index > &;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        static auto findAll (
                ElementType                 const * pSource,
                Size                                sourceLength,
                ElementType                 const * toBeFound,
                Size                                toBeFoundLength,
                Index                             * pIndices,
                Size                                maxIndexCount
        ) noexcept -> Size;

    public:                                                                         /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto contains (   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp, misc-non-private-member-variables-in-classes) */
                ElementType const * pBuffer,
                Size                length,
                ElementType         character
        ) noexcept -> bool;

    public:                                 /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __ArgumentType,    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: isConvertibleToBaseStringView < __ArgumentType, __CharType > () > = 0
        > __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                __ArgumentType && argumentType
        ) noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                __hidden :: __impl :: __BaseStringView < __CharType > const & string
        ) noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                ElementType character
        ) noexcept -> Size;

    public: /* NOLINT(readability-redundant-access-specifiers) */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                bool value
        ) noexcept -> Size;

    public:                             /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __NumericType, /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: isIntegralToString < __CharType, __NumericType > () > = 0
        > __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                __NumericType value
        ) noexcept -> Size;

    public:                                     /* NOLINT(readability-redundant-access-specifiers) */
        template <
                typename __FloatingPointType,   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                meta :: EnableIf < meta :: isFloatingPoint < __FloatingPointType > () > = 0
        > __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArgument (
                __FloatingPointType value
        ) noexcept -> Size;

    public:                                         /* NOLINT(readability-redundant-access-specifiers) */
        template < typename ... __ArgumentTypes >   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        __CDS_NoDiscard __CDS_MaybeUnused __CDS_cpplang_ConstexprConditioned static auto stringLengthOfArguments (
                __ArgumentTypes && ... arguments
        ) noexcept -> Size;
    };

} /* namespace cds */

#endif /* __CDS_STRING_STRING_UTILS_HPP__ */
