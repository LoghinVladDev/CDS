//
// Created by loghin on 6/4/22.
//

#ifndef __CDS_EX_STRING_STRING_UTILS_HPP__
#define __CDS_EX_STRING_STRING_UTILS_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace experimental {

        template < typename CharType >
        class StringUtils {

        public:
            using ElementType = CharType;

        public:
            StringUtils () noexcept = delete;

        public:
            static sint8 const lesser       { -1 };

        public:
            static sint8 const equal        { 0 };

        public:
            static sint8 const greater      { 1 };

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
            template < typename OtherCharType, meta :: EnableIf < ! meta :: isSame < OtherCharType, CharType > () && sizeof ( CharType ) >= sizeof ( OtherCharType ) > = 0 >
            __CDS_cpplang_ConstexprConditioned static auto copy (
                    ElementType         * pDestination,
                    Size                  destinationOffset,
                    OtherCharType const * pSource,
                    Size                  sourceOffset,
                    Size                  length,
                    bool                  writeTerminator = true
            ) noexcept -> ElementType *;

        public:
            template < typename NumericType, meta :: EnableIf < meta :: isUnsigned < NumericType > () > = 0 >
            __CDS_cpplang_ConstexprConditioned static auto integerLength (
                    NumericType value,
                    uint8       base = 10U
            ) noexcept -> uint8;

        public:
            template < typename NumericType, meta :: EnableIf < meta :: isSigned < NumericType > () > = 0 >
            __CDS_cpplang_ConstexprConditioned static auto integerLength (
                    NumericType value,
                    uint8       base = 10U
            ) noexcept -> uint8;

        public:
            template < typename NumericType, meta :: EnableIf < meta :: isUnsigned < NumericType > () > = 0 >
            __CDS_cpplang_ConstexprConditioned static auto writeInteger (
                    ElementType           * pDestination,
                    Size                    offset,
                    NumericType             value,
                    uint8                   valueLength,
                    Size                  * pOffsetAfterWrite
            ) noexcept -> ElementType *;

        public:
            template < typename NumericType, meta :: EnableIf < meta :: isSigned < NumericType > () > = 0 >
            __CDS_cpplang_ConstexprConditioned static auto writeInteger (
                    ElementType           * pDestination,
                    Size                    offset,
                    NumericType             value,
                    uint8                   valueLength,
                    Size                  * pOffsetAfterWrite
            ) noexcept -> ElementType *;

        public:
            template < template < typename ... > class CollectionType >
            static auto find (
                    ElementType                 const * pSource,
                    Size                                sourceLength,
                    ElementType                 const * toBeFound,
                    Size                                toBeFoundLength,
                    Size                                maxCount,
                    CollectionType < Index >          & storeIn
            ) noexcept -> CollectionType < Index > &;

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
            template < template < typename ... > class CollectionType >
            static auto findAll (
                    ElementType                 const * pSource,
                    Size                                sourceLength,
                    ElementType                 const * toBeFound,
                    Size                                toBeFoundLength,
                    CollectionType < Index >          & storeIn
            ) noexcept -> CollectionType < Index > &;

        public:
            __CDS_NoDiscard __CDS_cpplang_ConstexprConditioned static auto contains (
                    ElementType const * pBuffer,
                    Size                length,
                    ElementType         character
            ) noexcept -> bool;
        };
    }
}

#endif // __CDS_EX_STRING_STRING_UTILS_HPP__
