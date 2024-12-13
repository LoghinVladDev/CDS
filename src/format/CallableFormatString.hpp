//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_CALLABLE_FORMAT_STRING_HPP
#define CDS_FORMAT_CALLABLE_FORMAT_STRING_HPP
#pragma once

#include <cds/StringView>
#include "FormatString.hpp"
#include "FormatterVisitorTable.hpp"

namespace cds {
namespace impl {
namespace fmt {
template <typename C, typename U> class CallableFormatString {
  using SV = BaseStringView<C, U>;
public:
  template <typename Fmt> CDS_ATTR(2(implicit, consteval(20, constexpr(14))))
  CallableFormatString(Fmt const& fmtStr) noexcept : _fmtStr{fmtStr} {}

  template <typename... Args> CDS_ATTR(nodiscard) auto operator()(Args&&... args)
      const CDS_ATTR(noexcept(false)) -> BaseString<C, U> {
    BaseString<C, U> out;
    DynamicFormatString<C, U, Args&&...> fmtStr{_fmtStr};
    visitFormattersForFormat(out, fmtStr, forwardAsTuple(fwd<Args>(args)...));
    return out;
  }

private:
  SV _fmtStr;
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_CALLABLE_FORMAT_STRING_HPP
