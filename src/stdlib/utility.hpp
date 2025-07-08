//
// Created by loghin on 2/26/24.
//

#ifndef CDS_STDLIB_UTILITY_HPP
#define CDS_STDLIB_UTILITY_HPP
#pragma once

#include <cds/meta/Compiler>
#include <cds/meta/StdLib>

#if CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_safe)
#include <utility>
#elif CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_unsafe)
namespace std {
#if CDS_ATTR(libcxx)
inline namespace __1 {
template <typename> struct tuple_size;
template <size_t, typename> struct tuple_element;
}
#elif CDS_ATTR(stdlibcxx)
template <typename> struct tuple_size;
template <size_t, typename> struct tuple_element;
#elif CDS_ATTR(msvclibcxx)
template <typename> struct tuple_size;
template <size_t, typename> struct tuple_element;
#endif
} // namespace std
#endif

#endif // CDS_STDLIB_UTILITY_HPP
