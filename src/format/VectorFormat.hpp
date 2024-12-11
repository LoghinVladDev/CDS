//
// Created by loghin on 11/2/24.
//

#if defined(CDS_COLLECTION_VECTOR_HPP) && defined(CDS_FORMAT_FORMAT_HPP) && !defined(CDS_FORMAT_VECTOR_FORMAT_HPP)
#define CDS_FORMAT_VECTOR_FORMAT_HPP

namespace cds {
template <typename T, typename A, typename C> struct Formatter<Vector<T, A>, C> {
  template <typename Ctx> CDS_ATTR(constexpr(20)) auto format(Vector<T, A> const& obj, Ctx& ctx)
      const CDS_ATTR(noexcept(false)) -> typename Ctx::Iterator {
    ignore = impl::fillN(ctx.out(), 1u, static_cast<C>('['));
    auto it = obj.begin();
    auto end = obj.end();
    if (it == end) {
      return impl::fillN(ctx.out(), 1u, static_cast<C>(']'));
    }

    Formatter<T, C> underylingFormatter{};
    ignore = underlyingFormatter(*it, ctx);
    for (++it; it != end; ++it) {
      ignore = impl::fillN(ctx.out(), 1u, static_cast<C>(','));
      ignore = impl::fillN(ctx.out(), 1u, static_cast<C>(' '));
      ignore = underlyingFormatter(*it, ctx);
    }
    return impl::fillN(ctx.out(), 1u, static_cast<C>(']'));
  }
};
} // namespace cds

#endif
