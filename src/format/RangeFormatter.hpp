//
// Created by loghin on 12/11/24.
//

#ifndef CDS_FORMAT_RANGE_FORMATTER_HPP
#define CDS_FORMAT_RANGE_FORMATTER_HPP
#pragma once

#include <cds/Tuple>
#include <cds/meta/Base>
#include <cds/exception/FormatException>

#include "FormatParseInvoker.hpp"
#include "Formatter.hpp"
#include "StandardFormattingSpecificationComponents.hpp"
#include "TupleLikeFormatter.hpp"

namespace cds {
namespace impl {
namespace fmt {
using meta::EnableIf;
using meta::False;
using meta::True;
using meta::Void;

template <typename...> struct RangeLike;

template <typename, typename = void> struct IsRangeMapLikeEntry : False {};
template <typename T> struct IsRangeMapLikeEntry<T, Void<decltype(Formatter<T>::type)>> : True {};

template <typename T, EnableIf<IsRangeMapLikeEntry<T>> = 0> CDS_ATTR(constexpr(14))
auto formatRangeEnableUnderlyingMapLikeFormatting(Formatter<T>& fmt) noexcept -> void {
  fmt.type = FormatTupleType::Map;
}

template <typename T, EnableIf<Not<IsRangeMapLikeEntry<T>>> = 0> CDS_ATTR(constexpr(14))
auto formatRangeEnableUnderlyingMapLikeFormatting(Formatter<T>& fmt) CDS_ATTR(noexcept(false)) -> void {
  ignore = fmt;
  throw FormatException("Cannot use map-like tuple presentation type unless underlying type is a "
                        "tuple-like with exactly two underlying types");
}

template <typename I, typename S> class FormatRangeParseContext {
public:
  using Iterator = I;

  CDS_ATTR(2(explicit, constexpr(11))) FormatRangeParseContext(I b, S e) noexcept : _b{b}, _e{e} {}

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

template <typename I> class FormatRangeContext {
public:
  using Iterator = I;

  CDS_ATTR(2(explicit, constexpr(11))) FormatRangeContext(I out) noexcept : _out{out} {}

  CDS_ATTR(2(nodiscard, constexpr(11))) auto out() const noexcept -> Iterator {
    return _out;
  }

private:
  I _out;
};

template <template <typename...> class R, typename T, typename C> struct RangeFormatter :
    FormatFillAlignComponent<RangeLike<T>, C>,
    FormatWidthOnlyComponent<C>{
  using FormatFillAlignComponent<RangeLike<T>, C>::parseFillAlign;
  using FormatFillAlignComponent<RangeLike<T>, C>::formatFillAlign;
  using FormatFillAlignComponent<RangeLike<T>, C>::fillAlignSpecification;
  using FormatWidthOnlyComponent<C>::parseWidth;
  using FormatWidthOnlyComponent<C>::widthSpecification;
  using ST = StringTraits<C>;
  using SU = StringUtils<C, ST>;

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(14))) auto parse(Ctx& ctx) CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    auto end = ctx.end();
    auto it = parseWidth(parseFillAlign(ctx.begin(), end), end);
    if (it == end) {
      FormatRangeParseContext<RemoveCVRef<decltype(end)>, RemoveCVRef<decltype(end)>> subCtx{end, end};
      ignore = FormatParseInvoker<Formatter<T>, RemoveCVRef<decltype(subCtx)>>::parse(underlyingFormatter, subCtx);
      return it;
    }

    if (*it == static_cast<C>('n')) {
      omitOpenClose = true;
      ++it;
    }

    if (*it == static_cast<C>('m')) {
      mapLike = true;
      ++it;
    }

    if (*it == static_cast<C>(':')) {
      FormatRangeParseContext<RemoveCVRef<decltype(it)>, RemoveCVRef<decltype(end)>> subCtx{++it, end};
      it = FormatParseInvoker<Formatter<T>, RemoveCVRef<decltype(subCtx)>>::parse(underlyingFormatter, subCtx);
    } else {
      FormatRangeParseContext<RemoveCVRef<decltype(end)>, RemoveCVRef<decltype(end)>> subCtx{end, end};
      ignore = FormatParseInvoker<Formatter<T>, RemoveCVRef<decltype(subCtx)>>::parse(underlyingFormatter, subCtx);
    }

    if (mapLike) {
      formatRangeEnableUnderlyingMapLikeFormatting<T>(underlyingFormatter);
    }

    if (it == end) {
      return it;
    }

    throw FormatException("Extraneous characters in format string");
  }

  template <typename Ctx, typename T0> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto format(T0 const& rangeLike, Ctx& ctx) const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    auto const maybeRequestedWidth = widthSpecification.width.transform(&FormatSizeSpecification::size).getOr(nullopt);
    if (maybeRequestedWidth) {
      using S = BaseString<C, SU>;
      S elementsAsString;
      BackInserterIterator<S> out{elementsAsString};
      auto it = cds::begin(rangeLike);
      auto end = cds::end(rangeLike);
      if (it != end) {
        FormatRangeContext<RemoveCVRef<decltype(out)>> subCtx0{out};
        out = underlyingFormatter.format(*it, subCtx0);
        for (++it; it != end; ++it) {
          *out = static_cast<C>(',');
          *++out = static_cast<C>(' ');
          FormatRangeContext<RemoveCVRef<decltype(out)>> subCtx1{out};
          out = underlyingFormatter.format(*it, subCtx1);
        }
      }

      return formatFillAlign(
          maybeRequestedWidth, ctx.out(), elementsAsString, elementsAsString.size() + (omitOpenClose ? 0u : 2u),
          [this](S const& value0, BackInserterIterator<S> out0) {
            if (!omitOpenClose && !mapLike) {
              *out0 = static_cast<C>('[');
            } else if (!omitOpenClose) {
              *out0 = static_cast<C>('{');
            }
            out0 = impl::copy(value0.begin(), value0.end(), ++out0);
            if (!omitOpenClose && !mapLike) {
              *out0 = static_cast<C>(']');
            } else if (!omitOpenClose) {
              *out0 = static_cast<C>('}');
            }
            return out0;
          }
      );
    }

    auto out = ctx.out();
    if (!omitOpenClose && !mapLike) {
      *out = static_cast<C>('[');
    } else if (!omitOpenClose) {
      *out = static_cast<C>('{');
    }

    auto it = cds::begin(rangeLike);
    auto end = cds::end(rangeLike);
    if (it != end) {
      out = underlyingFormatter.format(*it, ctx);
      for (++it; it != end; ++it) {
        *out = static_cast<C>(',');
        *++out = static_cast<C>(' ');
        out = underlyingFormatter.format(*it, ctx);
      }
    }

    if (!omitOpenClose && !mapLike) {
      *out = static_cast<C>(']');
    } else if (!omitOpenClose) {
      *out = static_cast<C>('}');
    }

    return out;
  }

  bool omitOpenClose {false};
  bool mapLike {false};
  Formatter<T> underlyingFormatter;
};
} // namespace fmt
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_FORMAT_RANGE_FORMATTER_HPP
