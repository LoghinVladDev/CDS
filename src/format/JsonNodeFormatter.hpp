//
// Created by loghin on 6/25/25.
//

#if defined(CDS_FORMAT_FORMAT_HPP) && defined(CDS_DS_JSON_NODE_DEF_HPP) && !defined(CDS_FORMAT_JSON_NODE_FORMATTER_HPP)
#define CDS_FORMAT_JSON_NODE_FORMATTER_HPP

namespace cds {
namespace impl {
namespace fmt {
enum class PermissiveFormatTypeFlagBits : U16 {
  Binary = 0x0001u,
  Character = 0x0002u,
  Decimal = 0x0004u,
  Octal = 0x0008u,
  Hex = 0x0010u,
  IntegralUppercase = 0x0020u,
  Escaped = 0x0040u,
  Scientific = 0x0080u,
  Fixed = 0x0100u,
  General = 0x0200u,
  Pointer = 0x0400u,
  String = 0x0800u,
  FloatingUppercase = 0x1000u,
  PointerUppercase = 0x2000u,
  OmitOpenClose = 0x4000u,
  MapLike = 0x8000u,
};

using PermissiveFormatTypeFlags = U16;

template <typename C> CDS_ATTR(2(nodiscard, constexpr(14))) auto formatTypeSpecificationPermissive(C typeChar)
    CDS_ATTR(noexcept(false)) -> PermissiveFormatTypeFlags {
  switch (typeChar) {
    case static_cast<C>('a'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Hex);
    case static_cast<C>('A'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Hex)
        | static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::FloatingUppercase);
    case static_cast<C>('e'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Scientific);
    case static_cast<C>('E'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Scientific)
        | static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::FloatingUppercase);
    case static_cast<C>('f'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Fixed);
    case static_cast<C>('F'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Fixed)
        | static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::FloatingUppercase);
    case static_cast<C>('g'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::General);
    case static_cast<C>('G'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::General)
        | static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::FloatingUppercase);
    case static_cast<C>('b'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Binary);
    case static_cast<C>('B'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Binary)
        | static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::IntegralUppercase);
    case static_cast<C>('c'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Character);
    case static_cast<C>('d'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Decimal);
    case static_cast<C>('o'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Octal);
    case static_cast<C>('x'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Hex);
    case static_cast<C>('X'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Hex)
        | static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::IntegralUppercase);
    case static_cast<C>('p'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Pointer);
    case static_cast<C>('P'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Pointer)
        | static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::PointerUppercase);
    case static_cast<C>('?'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Escaped);
    case static_cast<C>('s'): return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::String);
    case static_cast<C>('n'):
      return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::OmitOpenClose);
    case static_cast<C>('m'):
      return static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::MapLike);
    default:
      throw FormatException("Presentation type specifier is invalid");
  }
}

using json::impl::JsonNull;
using json::impl::JsonBool;
using json::impl::JsonNumberIntegral;
using json::impl::JsonNumberFloating;
using json::impl::JsonString;
using json::impl::JsonArrayBase;
using json::impl::JsonObjectBase;

template <typename> struct PermissiveFormatTypeFilter {
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(PermissiveFormatTypeFlags) const noexcept
      -> FormatTypeFlags {
    return 0;
  }
};

template <> struct PermissiveFormatTypeFilter<JsonBool> {
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(PermissiveFormatTypeFlags) const noexcept
      -> FormatTypeFlags {
    return static_cast<FormatTypeFlags>(FormatTypeFlagBits::String);
  }
};

template <> struct PermissiveFormatTypeFilter<JsonNumberIntegral> {
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(PermissiveFormatTypeFlags flags) const noexcept
      -> FormatTypeFlags {
    FormatTypeFlags sanitized = 0u;
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Binary))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Binary);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Character))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Character);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Decimal))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Decimal);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Octal))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Octal);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Hex))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Hex);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::IntegralUppercase))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Uppercase);
    }

    if (sanitized == 0u) {
      sanitized = static_cast<FormatTypeFlags>(FormatTypeFlagBits::Decimal);
    }

    return sanitized;
  }
};

template <> struct PermissiveFormatTypeFilter<JsonNumberFloating> {
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(PermissiveFormatTypeFlags flags) const noexcept
      -> FormatTypeFlags {
    FormatTypeFlags sanitized = 0u;
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Hex))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Hex);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Scientific))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Scientific);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Fixed))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Fixed);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::General))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::General);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::FloatingUppercase))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Uppercase);
    }

    if (sanitized == 0u) {
      sanitized = static_cast<FormatTypeFlags>(FormatTypeFlagBits::General);
    }

    return sanitized;
  }
};

template <> struct PermissiveFormatTypeFilter<JsonString> {
  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator()(PermissiveFormatTypeFlags flags) const noexcept
      -> FormatTypeFlags {
    FormatTypeFlags sanitized = 0u;
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::String))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::String);
    }
    if (0 != (flags & static_cast<PermissiveFormatTypeFlags>(PermissiveFormatTypeFlagBits::Escaped))) {
      sanitized |= static_cast<FormatTypeFlags>(FormatTypeFlagBits::Escaped);
    }

    if (sanitized == 0u) {
      sanitized = static_cast<FormatTypeFlags>(FormatTypeFlagBits::String);
    }

    return sanitized;
  }
};

template <typename> struct PermissiveFormatAlternateFilter {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(bool const value) const noexcept -> bool {
    return value;
  }
};

template <> struct PermissiveFormatAlternateFilter<JsonBool> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(bool) const noexcept -> bool {
    return false;
  }
};

template <> struct PermissiveFormatAlternateFilter<JsonString> {
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(bool) const noexcept -> bool {
    return false;
  }
};

template <typename C, typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
auto formatParseTypePermissive(I it, S end) CDS_ATTR(noexcept(false))
    -> Tuple<I, Optional<FormatTypeFlags>, Optional<BaseStringView<C>>> {
  if (it == end) {
    return {it, nullopt, nullopt};
  }

  FormatTypeFlags flags = 0u;
  while (it != end && *it != static_cast<C>('}') && *it != static_cast<C>(':')) {
    flags |= formatTypeSpecificationPermissive<C>(*it);
    ++it;
  }

  Optional<BaseStringView<C>> remainingFormatString{};
  if (it != end && *it == static_cast<C>(':')) {
    auto first = ++it;
    while (it != end && *it != static_cast<C>('}')) {
      ++it;
    }

    remainingFormatString = BaseStringView<C>{&*first, it - first};
  }

  return {it, flags, remainingFormatString};
}
} // namespace fmt
} // namespace impl

template <typename C, typename B, typename A> struct Formatter<json::impl::JsonNodeBase<B, A>, C> :
    impl::fmt::FormatFillAlignComponent<C>,
    impl::fmt::FormatNumberComponent<C>,
    impl::fmt::FormatWidthComponent<C> {
  using impl::fmt::FormatFillAlignComponent<C>::parseFillAlign;
  using impl::fmt::FormatFillAlignComponent<C>::formatFillAlign;
  using impl::fmt::FormatFillAlignComponent<C>::fillAlignSpecification;
  using impl::fmt::FormatNumberComponent<C>::parseNumber;
  using impl::fmt::FormatNumberComponent<C>::numberSpecification;
  using impl::fmt::FormatWidthComponent<C>::parseWidth;
  using impl::fmt::FormatWidthComponent<C>::widthSpecification;

  Optional<impl::fmt::FormatTypeFlags> permissiveTypeFlags {nullopt};
  Optional<impl::BaseStringView<C>> underlyingFormatString;

  template <typename I, typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto parseTypePermissive(I begin, S end) noexcept -> I {
    cds::tie(begin, permissiveTypeFlags, underlyingFormatString) = impl::fmt::formatParseTypePermissive<C>(begin, end);
    return begin;
  }

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(14))) auto parse(Ctx& ctx) CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    auto end = ctx.end();
    auto it = parseTypePermissive(parseWidth(parseNumber(parseFillAlign(ctx.begin(), end), end), end), end);
    if (it == ctx.end()) {
      return it;
    }

    throw FormatException("Extraneous characters in format string");
  }

  template <typename T> CDS_ATTR(constexpr(14)) auto copyIntoFormatter(impl::fmt::StandardFormatter<T, C>& fmt)
      const noexcept -> void {
    fmt.fillAlignSpecification = fillAlignSpecification;
    fmt.widthSpecification = widthSpecification;
    fmt.numberSpecification = numberSpecification;
    fmt.numberSpecification.alternate =
        impl::fmt::PermissiveFormatAlternateFilter<T>{}(fmt.numberSpecification.alternate);
    fmt.typeFlags = impl::fmt::PermissiveFormatTypeFilter<T>{}(permissiveTypeFlags.getOr(0u));
  }

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto formatNull(Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    impl::fmt::StringFormatter<C, C> strFormatter;
    copyIntoFormatter(strFormatter);

    auto permissiveFlags = permissiveTypeFlags.getOr(0u);
    if (0 != (permissiveFlags & static_cast<impl::fmt::PermissiveFormatTypeFlags>(
        impl::fmt::PermissiveFormatTypeFlagBits::PointerUppercase
    ))) {
      return strFormatter.format("NULL", ctx);
    }
    return strFormatter.format("null", ctx);
  }

  template <typename F, typename V, typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto formatPrimitive(V value, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    F formatter;
    copyIntoFormatter(formatter);
    return formatter.format(value, ctx);
  }

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto formatString(json::impl::JsonString const& str, Ctx& ctx) const CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    impl::fmt::StringFormatter<json::impl::JsonString, C> strFormatter;
    copyIntoFormatter(strFormatter);
    strFormatter.numberSpecification.alternate = false;
    strFormatter.typeFlags =
        impl::fmt::PermissiveFormatTypeFilter<json::impl::JsonString>{}(permissiveTypeFlags.getOr(0));
    auto out = ctx.out();
    *out = static_cast<C>('"');
    auto subCtx = ctx.from(out);
    out = strFormatter.format(str, subCtx);
    *out = static_cast<C>('"');
    return out;
  }

  template <typename N = json::impl::JsonNodeBase<>, typename V, typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto formatRange(V const& range, Ctx& ctx, StringView mapFormatOverride = {}) const CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    impl::fmt::RangeFormatter<N, C> rangeFormatter;

    rangeFormatter.omitOpenClose = 0 != (permissiveTypeFlags.getOr(0)
        & static_cast<impl::fmt::PermissiveFormatTypeFlags>(impl::fmt::PermissiveFormatTypeFlagBits::OmitOpenClose));
    rangeFormatter.mapLike = 0 != (permissiveTypeFlags.getOr(0)
    & static_cast<impl::fmt::PermissiveFormatTypeFlags>(impl::fmt::PermissiveFormatTypeFlagBits::MapLike));

    StringView usedUnderlyingFormatString = underlyingFormatString.getOr(mapFormatOverride);
    if (mapFormatOverride) {
      usedUnderlyingFormatString = mapFormatOverride;
      rangeFormatter.mapLike = true;
    }
    impl::fmt::FormatRangeParseContext<
        // explicitly qualify, deduced arg types req. c++17
        decltype(usedUnderlyingFormatString.begin()),
        decltype(usedUnderlyingFormatString.end())
    > subCtx{usedUnderlyingFormatString.begin(), usedUnderlyingFormatString.end()};
    ignore = impl::fmt::FormatParseInvoker<
        Formatter<N, C>,
        meta::RemoveCVRef<decltype(subCtx)>
    >::parse(rangeFormatter.underlyingFormatter, subCtx);
    return rangeFormatter.format(range, ctx);
  }

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto format(json::impl::JsonNodeBase<B, A> const& value, Ctx& ctx) const CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    if (value.isNull()) {
      return formatNull(ctx);
    }

    if (value.isBool()) {
      return formatPrimitive<impl::fmt::BoolFormatter<C>>(value.getBool(), ctx);
    }

    if (value.isIntegral()) {
      return formatPrimitive<impl::fmt::IntegralFormatter<json::impl::JsonNumberIntegral, C>>(
          value.getInt(), ctx
      );
    }

    if (value.isFloating()) {
      return formatPrimitive<impl::fmt::FloatingFormatter<json::impl::JsonNumberFloating, C>>(
          value.getDouble(), ctx
      );
    }

    if (value.isString()) {
      return formatString(value.getString(), ctx);
    }

    if (value.isArray()) {
      return formatRange(value.getArray(), ctx);
    }

    if (value.isObject()) {
      if (permissiveTypeFlags.getOr(0) == 0 && !underlyingFormatString) {
        return formatRange<MapEntry<String, json::impl::JsonNodeBase<>>>(value.getObject(), ctx, "m:#:");
      }
      return formatRange<MapEntry<String, json::impl::JsonNodeBase<>>>(value.getObject(), ctx);
    }

    assert(false && "undefined behavior");
    return ctx.out();
  }
};
} // namespace cds

#endif // #if defined(CDS_FORMAT_FORMAT_HPP) && defined(CDS_DS_JSON_NODE_DEF_HPP) && !defined(CDS_FORMAT_JSON_NODE_FORMATTER_HPP)
