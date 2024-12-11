//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_STANDARD_FORMATTERS_HPP
#define CDS_FORMAT_STANDARD_FORMATTERS_HPP

#include "Formatter.hpp"
#include "StandardFormatSpecification.hpp"

namespace cds {
namespace impl {
namespace fmt {
template <typename T, typename C> struct IntegralFormatter : StandardFormatter<T, C> {
  using StandardFormatter<T, C>::typeFlags;
  using StandardFormatter<T, C>::formatChar;
  using StandardFormatter<T, C>::formatInteger;

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto format(T value, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    if ((typeFlags & FormatTypeFlagBits::Character) != 0u) {
      return formatChar(value, ctx);
    }
    return formatInteger(value, ctx);
  }
};

template <typename C> struct CharFormatter : StandardFormatter<C, C> {
  using StandardFormatter<C, C>::typeFlags;
  using StandardFormatter<C, C>::formatChar;
  using StandardFormatter<C, C>::formatInteger;

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto format(C value, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    if ((typeFlags & FormatTypeFlagBits::Character) != 0u) {
      return formatChar(value, ctx);
    }
    return formatInteger(static_cast<unsigned>(value), ctx);
  }
};

template <typename C> struct BoolFormatter : StandardFormatter<bool, C> {
  using StandardFormatter<bool, C>::typeFlags;
  using StandardFormatter<bool, C>::formatString;
  using StandardFormatter<bool, C>::formatInteger;

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto format(bool value, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    if ((typeFlags & FormatTypeFlagBits::String) == 0u) {
      return formatInteger(static_cast<unsigned>(value), ctx);
    }
    auto asStr = value
               ? BaseStringView<C>{StringTraits<C>::Constants::_true}
               : BaseStringView<C>{StringTraits<C>::Constants::_false};
    return formatString(asStr, ctx);
  }
};

template <typename T, typename C> struct StringFormatter : StandardFormatter<C, C> {
  using StandardFormatter<C, C>::formatString;

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto format(BaseStringView<C> value, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    return formatString(value, ctx);
  }
};
} // namespace fmt
} // namespace impl

template <typename C> struct Formatter<C, C> : impl::fmt::CharFormatter<C> {};
template <typename C> struct Formatter<bool, C> : impl::fmt::BoolFormatter<C> {};

template <typename C> struct Formatter<U16, C> : impl::fmt::IntegralFormatter<U16, C> {};
template <typename C> struct Formatter<U32, C> : impl::fmt::IntegralFormatter<U32, C> {};
template <typename C> struct Formatter<U64, C> : impl::fmt::IntegralFormatter<U64, C> {};
template <typename C> struct Formatter<S16, C> : impl::fmt::IntegralFormatter<S16, C> {};
template <typename C> struct Formatter<S32, C> : impl::fmt::IntegralFormatter<S32, C> {};
template <typename C> struct Formatter<S64, C> : impl::fmt::IntegralFormatter<S64, C> {};

template <typename C, typename U, typename A>
struct Formatter<impl::BaseString<C, U, A>, C> : impl::fmt::StringFormatter<impl::BaseString<C, U, A>, C> {};

template <typename C, typename U>
struct Formatter<impl::BaseStringView<C, U>, C> : impl::fmt::StringFormatter<impl::BaseStringView<C, U>, C> {};

template <typename C, typename T, typename A>
struct Formatter<std::basic_string<C, T, A>, C> : impl::fmt::StringFormatter<std::basic_string<C, T, A>, C> {};

#if CDS_ATTR(cpp17)
template <typename C, typename T>
struct Formatter<std::basic_string_view<C, T>, C> : impl::fmt::StringFormatter<std::basic_string_view<C, T>, C> {};
#endif // #if CDS_ATTR(cpp17)

template <typename C> struct Formatter<C const*, C> : impl::fmt::StringFormatter<C const*, C> {};
template <typename C> struct Formatter<C*, C> : impl::fmt::StringFormatter<C*, C> {};
template <typename C> struct Formatter<C[], C> : impl::fmt::StringFormatter<C[], C> {};
template <typename C, Size n> struct Formatter<C[n], C> : impl::fmt::StringFormatter<C[n], C> {};
} // namespace cds

#endif // #ifndef CDS_FORMAT_STANDARD_FORMATTERS_HPP
