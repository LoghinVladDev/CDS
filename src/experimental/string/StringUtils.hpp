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

            constexpr static auto isUpper (
                    ElementType character
            ) noexcept -> bool;

            constexpr static auto isLower (
                    ElementType character
            ) noexcept -> bool;

            constexpr static auto isDigit (
                    ElementType character
            ) noexcept -> bool;

            constexpr static auto isLetter (
                    ElementType character
            ) noexcept -> bool;

            constexpr static auto isAlpha (
                    ElementType character
            ) noexcept -> bool;

            constexpr static auto isVowel (
                    ElementType character
            ) noexcept -> bool;

            constexpr static auto isConsonant (
                    ElementType character
            ) noexcept -> bool;

            constexpr static auto lower (
                    ElementType character
            ) noexcept -> ElementType;

            constexpr static auto upper (
                    ElementType character
            ) noexcept -> ElementType;
        };
    }
}

#endif // __CDS_EX_STRING_STRING_UTILS_HPP__
