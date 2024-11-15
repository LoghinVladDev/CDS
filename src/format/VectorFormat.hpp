//
// Created by loghin on 11/2/24.
//

#if defined(CDS_COLLECTION_VECTOR_HPP) && defined(CDS_FORMAT_FORMAT_HPP) && !defined(CDS_FORMAT_VECTOR_FORMAT_HPP)
#define CDS_FORMAT_VECTOR_FORMAT_HPP

namespace cds {
namespace experimental {
namespace impl {
template <typename T, typename A> struct Formatter<Vector<T, A>> {
  template <typename S> CDS_ATTR(constexpr(14)) auto operator()(S& string, Vector<T> const& obj)
      const CDS_ATTR(noexcept(false)) -> void {
    using C = typename S::Char;
    string += static_cast<C>('[');
    auto it = obj.begin();
    auto end = obj.end();
    if (it == end) {
      string += static_cast<C>(']');
      return;
    }

    Formatter<T>{}(string, *it);
    for (++it; it != end; ++it) {
      string += static_cast<C>(',');
      string += static_cast<C>(' ');
      Formatter<T>{}(string, *it);
    }
    string += static_cast<C>(']');
  }
};
} // namespace impl
} // namespace experimental
} // namespace cds

#endif
