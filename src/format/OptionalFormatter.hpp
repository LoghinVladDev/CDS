//
// Created by loghin on 11/2/24.
//

#if defined(CDS_PRIMITIVE_OPTIONAL_HPP) && defined(CDS_FORMAT_FORMAT_HPP) && !defined(CDS_FORMAT_OPTIONAL_FORMAT_HPP)
#define CDS_FORMAT_OPTIONAL_FORMAT_HPP

namespace cds {
template <typename T, typename C> struct Formatter<Optional<T>, C> {
  template <typename Ctx> CDS_ATTR(constexpr(14)) auto parse(Ctx& ctx) CDS_ATTR(noexcept(false))
      -> typename Ctx::Iterator {
    return underlyingFormatter.parse(ctx);
  }

  template <typename Ctx> CDS_ATTR(constexpr(20)) auto format(Optional<T> const& obj, Ctx& ctx)
      const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    if (!obj) {
      char const nullAsString[] = "<nullopt>";
      impl::copy(cds::begin(nullAsString), cds::end(nullAsString), ctx.out());
      return ctx.out();
    }

    ignore = underlyingFormatter.format(*obj, ctx);
    return ctx.out();
  }

  Formatter<T, C> underlyingFormatter{};
};
} // namespace cds

#endif
