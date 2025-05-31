//
// Created by loghin on 2/26/24.
//

#ifndef CDS_STDLIB_ARRAY_HPP
#define CDS_STDLIB_ARRAY_HPP
#pragma once

#include <cds/meta/Compiler>
#include <cds/meta/StdLib>

#if CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_safe)
#include <array>
#elif CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_unsafe)
namespace std {
#if CDS_ATTR(libcxx)
inline namespace __1 {
template <typename, std::size_t> class array;
}
#elif CDS_ATTR(stdlibcxx)
template <typename, std::size_t> class array;
#elif CDS_ATTR(msvclibcxx)
template <typename, std::size_t> class array;
#endif
} // namespace std
#endif

#endif // CDS_STDLIB_ARRAY_HPP
