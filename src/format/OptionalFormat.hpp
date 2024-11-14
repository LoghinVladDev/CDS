//
// Created by loghin on 11/2/24.
//

#if defined(CDS_PRIMITIVE_OPTIONAL_HPP) && defined(CDS_FORMAT_FORMAT_HPP) && !defined(CDS_FORMAT_OPTIONAL_FORMAT_HPP)
#define CDS_FORMAT_OPTIONAL_FORMAT_HPP

namespace cds {
namespace experimental {
namespace impl {
template <typename T> struct Formatter<Optional<T>> {
  template <typename S> CDS_ATTR(constexpr(14)) auto operator()(S& string, Optional<T> const& obj)
      const CDS_ATTR(noexcept(false)) -> void {
    if (!obj) {
      string += "<nullopt>";
      return;
    }
    string += "<";
    Formatter<T>{}(string, *obj);
    string += ">";
  }
};
} // namespace impl
} // namespace experimental
} // namespace cds

#endif
