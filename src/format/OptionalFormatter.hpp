//
// Created by loghin on 11/2/24.
//

#if defined(CDS_PRIMITIVE_OPTIONAL_HPP) && defined(CDS_FORMAT_FORMAT_HPP) && !defined(CDS_FORMAT_OPTIONAL_FORMAT_HPP)
#define CDS_FORMAT_OPTIONAL_FORMAT_HPP

namespace cds {
template <typename T, typename C> struct Formatter<Optional<T>, C> {
  template <typename Ctx> CDS_ATTR(constexpr(20)) auto format(Optional<T> const& obj, Ctx& ctx)
      const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    // TODO: handle for other char types
    static_assert(cds::meta::IsSame<char, C>::value, "Unhandled CharType case");
    if (!obj) {
      char const def[] = "<nullopt>";
      return impl::copy(cds::begin(def), cds::end(def), ctx.out());
    }

    Formatter<T, C> underlyingFormatter{};
    ignore = impl::fillN(ctx.out(), 1u, static_cast<C>('<'));
    ignore = underlyingFormatter.format(*obj, ctx);
    return impl::fillN(ctx.out(), 1u, static_cast<C>('>'));
  }
};
} // namespace cds

#endif
