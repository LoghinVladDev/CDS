//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_BASE_STRING_VIEW_LITERALS_HPP__
#define __CDS_BASE_STRING_VIEW_LITERALS_HPP__

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
    namespace literals {

        constexpr auto operator ""_s (
                char const        * pString,
                std :: size_t       length
        ) noexcept -> __hidden :: __impl :: __BaseStringView < char > {

            return __hidden :: __impl :: __BaseStringView < char > (
                    pString,
                    length
            );
        }

        constexpr auto operator ""_s (
                wchar_t const     * pString,
                std :: size_t       length
        ) noexcept -> __hidden :: __impl :: __BaseStringView < wchar_t > {

            return __hidden :: __impl :: __BaseStringView < wchar_t > (
                    pString,
                    length
            );
        }

    }
}

#endif // __CDS_BASE_STRING_VIEW_LITERALS_HPP__
