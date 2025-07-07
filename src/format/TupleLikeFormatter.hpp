//
// Created by loghin on 11/2/24.
//

#ifndef CDS_FORMAT_TUPLE_LIKE_FORMATTER_HPP
#define CDS_FORMAT_TUPLE_LIKE_FORMATTER_HPP
#pragma once

#include <cds/meta/Base>
#include <cds/exception/FormatException>

#include "FormatParseInvoker.hpp"
#include "Formatter.hpp"
#include "StandardFormattingSpecificationComponents.hpp"

namespace cds {
namespace impl {
namespace fmt {
using meta::Bool;
using meta::EnableIf;
using meta::Int;
using meta::Gt;

template <typename...> struct TupleLike;

enum class FormatTupleType {
  Array,
  Map,
  None
};

template <typename I, typename S> class FormatTupleParseContext {
public:
  using Iterator = I;

  CDS_ATTR(2(explicit, constexpr(11))) FormatTupleParseContext(I b, S e) noexcept : _b{b}, _e{e} {}

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> Iterator {
    return _b;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Iterator {
    return _e;
  }

private:
  I _b;
  S _e;
};

template <typename I> class FormatTupleContext {
public:
  using Iterator = I;

  CDS_ATTR(2(explicit, constexpr(11))) FormatTupleContext(I out) noexcept : _out{out} {}

  CDS_ATTR(2(nodiscard, constexpr(11))) auto out() const noexcept -> Iterator {
    return _out;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto from(Iterator& iterator) const noexcept -> FormatTupleContext {
    ignore = iterator;
    return FormatTupleContext{_out};
  }

private:
  I _out;
};

template <
    typename /* C */, unsigned idx, typename I, typename S, typename... Fs,
    EnableIf<Bool<idx == sizeof...(Fs)>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14)))
auto formatParseTupleUnderlyingFormatters(
    I it, S end, Tuple<Fs...>& underlyingFormatters
) CDS_ATTR(noexcept(false)) -> I {
  ignore = it;
  ignore = end;
  ignore = underlyingFormatters;
  return it;
}

template <
    typename C, unsigned idx, typename I, typename S, typename... Fs,
    EnableIf<Bool<idx < sizeof...(Fs)>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14)))
auto formatParseTupleUnderlyingFormatters(
    I it, S end, Tuple<Fs...>& underlyingFormatters
) CDS_ATTR(noexcept(false)) -> I {
  for (auto nextSpecIt = it; nextSpecIt != end; ++nextSpecIt) {
    if (*nextSpecIt == static_cast<C>(':')) {
      FormatTupleParseContext<I, S> ctx{it, nextSpecIt};
      auto subIt = FormatParseInvoker<RemoveCVRef<decltype(get<idx>(underlyingFormatters))>, RemoveCVRef<decltype(ctx)>>
          ::parse(get<idx>(underlyingFormatters), ctx);
      assert(nextSpecIt == subIt && "Expected complete parse of underlying type");

      if (idx + 1 == sizeof...(Fs)) {
        throw FormatException("Number of format specifications exceeds tuple entry count and tuple specification");
      }

      return formatParseTupleUnderlyingFormatters<C, idx + 1>(nextSpecIt + 1, end, underlyingFormatters);
    }
  }

  FormatTupleParseContext<I, S> ctx{it, end};
  it = FormatParseInvoker<RemoveCVRef<decltype(get<idx>(underlyingFormatters))>, RemoveCVRef<decltype(ctx)>>
      ::parse(get<idx>(underlyingFormatters), ctx);
  return formatParseTupleUnderlyingFormatters<C, idx + 1>(it, end, underlyingFormatters);
}

template <
    unsigned idx, typename C, typename U, typename T, typename... Fs,
    EnableIf<Bool<(idx == sizeof...(Fs))>> = 0
> CDS_ATTR(constexpr(14))
auto formatFormatTupleUnderlyingFormatters(
    BaseString<C, U>& out, Tuple<Fs...> const& underlyingFormatters, T const& obj, FormatTupleType type
) CDS_ATTR(noexcept(false)) -> void {
  ignore = out;
  ignore = underlyingFormatters;
  ignore = obj;
  ignore = type;
}

template <
    unsigned idx, typename C, typename U, typename T, typename... Fs,
    EnableIf<Bool<(idx < sizeof...(Fs))>> = 0
> CDS_ATTR(constexpr(14))
auto formatFormatTupleUnderlyingFormatters(
    BaseString<C, U>& out, Tuple<Fs...> const& underlyingFormatters, T const& obj, FormatTupleType type
) CDS_ATTR(noexcept(false)) -> void {
  using S = BaseString<C, U>;
  using I = BackInserterIterator<S>;
  FormatTupleContext<I> separateCtx{I{out}};
  ignore = get<idx>(underlyingFormatters).format(get<idx>(obj), separateCtx);
  if (idx + 1 != sizeof...(Fs)) {
    if (type == FormatTupleType::Array) {
      out += static_cast<C>(',');
    } else if (type == FormatTupleType::Map) {
      out += static_cast<C>(':');
    }
    if (type != FormatTupleType::None) {
      out += static_cast<C>(' ');
    }
  }
  formatFormatTupleUnderlyingFormatters<idx + 1>(out, underlyingFormatters, obj, type);
}

template <
    typename C, unsigned idx, typename Ctx, typename T, typename... Fs,
    EnableIf<Bool<(idx == sizeof...(Fs))>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14)))
auto lazyFormatFormatTupleUnderlyingFormatters(
    Ctx& ctx, Tuple<Fs...> const& underlyingFormatters, T const& obj, FormatTupleType type
) CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
  ignore = underlyingFormatters;
  ignore = obj;
  ignore = type;
  return ctx.out();
}

template <
    typename C, unsigned idx, typename Ctx, typename T, typename... Fs,
    EnableIf<Bool<(idx < sizeof...(Fs))>> = 0
> CDS_ATTR(2(nodiscard, constexpr(14)))
auto lazyFormatFormatTupleUnderlyingFormatters(
    Ctx& ctx, Tuple<Fs...> const& underlyingFormatters, T const& obj, FormatTupleType type
) CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
  ignore = get<idx>(underlyingFormatters).format(get<idx>(obj), ctx);
  if (idx + 1 != sizeof...(Fs)) {
    if (type == FormatTupleType::Array) {
      *ctx.out() = static_cast<C>(',');
    } else if (type == FormatTupleType::Map) {
      *ctx.out() = static_cast<C>(':');
    }
    if (type != FormatTupleType::None) {
      *ctx.out() = static_cast<C>(' ');
    }
  }
  return lazyFormatFormatTupleUnderlyingFormatters<C, idx + 1>(ctx, underlyingFormatters, obj, type);
}

template <typename C, typename... T> struct TupleLikeFormatter :
    FormatFillAlignComponent<C>,
    FormatWidthOnlyComponent<C> {
  using FormatFillAlignComponent<C>::parseFillAlign;
  using FormatFillAlignComponent<C>::formatFillAlign;
  using FormatFillAlignComponent<C>::fillAlignSpecification;
  using FormatWidthOnlyComponent<C>::parseWidth;
  using FormatWidthOnlyComponent<C>::widthSpecification;
  using ST = StringTraits<C>;
  using SU = StringUtils<C, ST>;

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(14))) auto parse(Ctx& ctx) CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    auto end = ctx.end();
    auto it = parseWidth(parseFillAlign(ctx.begin(), end), end);
    if (it == end) {
      return formatParseTupleUnderlyingFormatters<C, 0>(it, end, underlyingFormatters);
    }

    if (*it == static_cast<C>('m')) {
      if (sizeof...(T) != 2) {
        throw FormatException("Cannot use map-like tuple presentation type with a "
                              "tuple-like without exactly two underlying types");
      }
      type = FormatTupleType::Map;
      ++it;
    } else if (*it == static_cast<C>('n')) {
      type = FormatTupleType::None;
      ++it;
    }

    if (*it == static_cast<C>(':')) {
      it = formatParseTupleUnderlyingFormatters<C, 0>(++it, end, underlyingFormatters);
    } else {
      ignore = formatParseTupleUnderlyingFormatters<C, 0>(end, end, underlyingFormatters);
    }

    if (it == ctx.end()) {
      return it;
    }

    throw FormatException("Extraneous characters in format string");
  }

  template <typename Ctx, typename T0> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto format(T0 const& tupleLike, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    auto const maybeRequestedWidth = widthSpecification.width.transform(&FormatSizeSpecification::size).getOr(nullopt);
    if (maybeRequestedWidth) {
      using S = BaseString<C, SU>;
      S entries;
      formatFormatTupleUnderlyingFormatters<0>(entries, underlyingFormatters, tupleLike, type);
      return formatFillAlign(
          maybeRequestedWidth, ctx.out(), entries, entries.size() + (type == FormatTupleType::Array ? 2u : 0u),
          [this](S const& value0, BackInserterIterator<S> out0) {
            if (type == FormatTupleType::Array) {
              *out0 = static_cast<C>('(');
            }
            out0 = impl::copy(value0.begin(), value0.end(), ++out0);
            if (type == FormatTupleType::Array) {
              *++out0 = static_cast<C>(')');
            }
            return out0;
          }
      );
    }

    if (type == FormatTupleType::Array) {
      *ctx.out() = static_cast<C>('(');
    }
    ignore = lazyFormatFormatTupleUnderlyingFormatters<C, 0>(ctx, underlyingFormatters, tupleLike, type);
    if (type == FormatTupleType::Array) {
      *ctx.out() = static_cast<C>(')');
    }
    return ctx.out();
  }

  Tuple<Formatter<RemoveCVRef<T>, C>...> underlyingFormatters;
  FormatTupleType type {FormatTupleType::Array};
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifdef CDS_FORMAT_TUPLE_LIKE_FORMATTER_HPP
