//
// Created by loghin on 31.03.2024.
//

#ifndef CDS_FORMAT_FORMAT_HPP
#define CDS_FORMAT_FORMAT_HPP

#include <cds/String>

namespace cds {
namespace impl {
class FormatString;
class CallableFormatString;

template <typename... Args> CDS_ATTR(2(nodiscard, constexpr(20)))
auto format(FormatString format, Args&&... args) CDS_ATTR(noexcept(false)) -> String;
} // namespace impl

using impl::format;

namespace literals {
CDS_ATTR(2(nodiscard, consteval(20, constexpr(14))))
auto operator ""_f(char const* fmt, std::size_t len) noexcept -> impl::CallableFormatString;
} // namespace literals
} // namespace cds

#endif // CDS_FORMAT_FORMAT_HPP
