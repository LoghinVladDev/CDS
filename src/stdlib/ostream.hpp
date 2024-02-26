//
// Created by loghin on 2/26/24.
//

#ifndef CDS_STDLIB_OSTREAM_HPP
#define CDS_STDLIB_OSTREAM_HPP

#include <cds/meta/Compiler>

#if CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_safe)
#include <ostream>
#elif CDS_ATTR(std_compat_mode) == CDS_ATTR(std_compat_unsafe)
namespace std {
template <typename, typename> class basic_ostream;
} // namespace std
#endif

#endif // CDS_STDLIB_OSTREAM_HPP
