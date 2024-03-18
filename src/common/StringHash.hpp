//
// Created by loghin on 3/17/24.
//

#if defined(CDS_STRING_ABSTRACT_HPP) && defined(CDS_FUNCTIONAL_HASH_HPP) && !defined(CDS_COMMON_STRING_HASH_HPP)
#define CDS_COMMON_STRING_HASH_HPP
namespace cds {
namespace functional {
template <typename T>
struct Hash <T, meta::EnableIf<meta::And<cds::impl::StringAbstract<T>, meta::Not<meta::IsPointer<T>>>, void>> {
  template <typename S> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto operator()(S&& value) const noexcept -> Size {
    using A = cds::impl::StringAbstract<S>;
    auto const len = A::length(cds::forward<S>(value));
    auto const str = A::data(cds::forward<S>(value));
    if (len == 0u) {
      return 0u;
    }

    Size exp = 1u;
    Size hvl = 0u;
    for (Size idx = len - 1u; idx > 0u; --idx) {
      Size constexpr exf = 31u;
      hvl += static_cast<Size>(str[idx]) * exp;
      exp *= exf;
    }

    return hvl + *str * exp;
  }
};
} // namespace functional
} // namespace cds
#endif
