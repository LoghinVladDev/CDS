//
// Created by loghin on 8/10/25.
//

#if defined(CDS_PRIMITIVE_EXPECTED_EXPECTED_DECL_HPP) && defined(CDS_FORMAT_FORMAT_HPP) && !defined(CDS_FORMAT_EXPECTED_FORMAT_HPP)
#define CDS_FORMAT_EXPECTED_FORMAT_HPP

#include "TupleLikeFormatter.hpp"

namespace cds {
template <typename T, typename E, typename C> struct Formatter<impl::Expected<T, E>, C> {
  template <typename Ctx> CDS_ATTR(constexpr(14)) auto parse(Ctx& ctx) CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    auto it = valueFormatter.parse(ctx);
    auto const end = ctx.end();

    if (it != end && *it == static_cast<C>(':')) {
      impl::fmt::FormatTupleParseContext<decltype(it), decltype(end)> underlyingCtx{it + 1, end};
      it = errorFormatter.parse(underlyingCtx);
    }

    if (it == end || *it != static_cast<C>('}')) {
      return it;
    }

    throw FormatException("Extraenous characters in format string");
  }

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20))) auto format(impl::Expected<T, E> const& value, Ctx& ctx)
      const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    if (value) {
      return valueFormatter.format(*value, ctx);
    }

    char const unexpectedIndicator[] = "unexpected<";
    impl::copy(cds::begin(unexpectedIndicator), cds::end(unexpectedIndicator), ctx.out());
    ignore = errorFormatter.format(value.error(), ctx);
    ctx.out() = static_cast<C>('>');
    return ctx.out();
  }

  Formatter<T, C> valueFormatter{};
  Formatter<E, C> errorFormatter{};
};

template <typename E, typename C> struct Formatter<impl::Unexpected<E>, C> {
  template <typename Ctx> CDS_ATTR(constexpr(14)) auto parse(Ctx& ctx) CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    auto it = errorFormatter.parse(ctx);
    if (it == ctx.end() || *it != static_cast<C>('}')) {
      return it;
    }

    throw FormatException("Extraenous characters in format string");
  }

  template <typename Ctx> CDS_ATTR(2(nodiscard, constexpr(20))) auto format(impl::Unexpected<E> const& value, Ctx& ctx)
      const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    char const unexpectedIndicator[] = "unexpected<";
    impl::copy(cds::begin(unexpectedIndicator), cds::end(unexpectedIndicator), ctx.out());
    ignore = errorFormatter.format(value.error(), ctx);
    ctx.out() = static_cast<C>('>');
    return ctx.out();
  }

  Formatter<E, C> errorFormatter{};
};
} // namespace cds

#endif // #ifndef CDS_FORMAT_EXPECTED_FORMAT_HPP
