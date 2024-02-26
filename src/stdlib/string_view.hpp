//
// Created by loghin on 2/26/24.
//

#ifndef CDS_STDLIB_STRING_VIEW_HPP
#define CDS_STDLIB_STRING_VIEW_HPP

#include <cds/meta/Compiler>
#include <cds/meta/StdLib>

#if CDS_ATTR(cpp17)
#if CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_safe)
#include <string_view>
#elif CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_unsafe)
namespace std {
#if CDS_ATTR(libcxx)
inline namespace __1 {
template <typename, typename> class basic_string_view;
}
#elif CDS_ATTR(stdlibcxx)
template <typename, typename> class basic_string_view;
#endif
} // namespace std
#endif
#endif

#endif // CDS_STDLIB_STRING_VIEW_HPP
