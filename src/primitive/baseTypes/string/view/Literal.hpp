//
// Created by loghin on 6/9/22.
//

#ifndef __CDS_BASE_STRING_VIEW_LITERALS_HPP__
#define __CDS_BASE_STRING_VIEW_LITERALS_HPP__ // NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp)
#pragma once

namespace cds { // NOLINT(modernize-concat-nested-namespaces)
namespace literals {
__CDS_cpplang_Consteval auto operator ""_s (
    char const*   pString,
    std::size_t   length
) noexcept -> __hidden::__impl::__BaseStringView <char> {
  return {pString, length};
}

__CDS_cpplang_Consteval auto operator ""_s (
    wchar_t const* pString,
    std::size_t    length
) noexcept -> __hidden::__impl::__BaseStringView <wchar_t> {
  return {pString, length};
}
} // namespace literals
} // namespace cds

#endif // __CDS_BASE_STRING_VIEW_LITERALS_HPP__
