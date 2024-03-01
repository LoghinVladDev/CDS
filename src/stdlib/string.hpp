//
// Created by loghin on 2/26/24.
//

#ifndef CDS_STDLIB_STRING_HPP
#define CDS_STDLIB_STRING_HPP
#pragma once

#include <cds/meta/Compiler>
#include <cds/meta/StdLib>

#if CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_safe)
#include <string>
#elif CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_unsafe)
namespace std {
#if CDS_ATTR(libcxx)
inline namespace __1 {
template <typename, typename, typename> class basic_string;
}
#elif CDS_ATTR(stdlibcxx)
inline namespace __cxx11 {
template <typename, typename, typename> class basic_string;
}
#elif CDS_ATTR(msvclibcxx)
template <typename, typename, typename> class basic_string;
#endif
} // namespace std
#endif

#endif // CDS_STDLIB_STRING_HPP
