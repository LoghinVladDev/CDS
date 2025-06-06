//
// Created by loghin on 3/17/24.
//

#if defined(CDS_PRIMITIVE_STRING_VIEW_BASE_HPP) && defined(CDS_PRIMITIVE_STRING_BASE_HPP) && !defined(CDS_COMMON_STRING_CONVERSION_HPP)
#define CDS_COMMON_STRING_CONVERSION_HPP
namespace cds {
namespace impl {
template <typename C, typename U> template <typename A>
CDS_ATTR(2(nodiscard, constexpr(20))) auto BaseStringView<C, U>::str(A&& alloc) const CDS_ATTR(noexcept(false))
    -> BaseString<C, U, A> {
  return {_data, _length, fwd<A>(alloc)};
}
} // namespace impl
} // namespace cds
#endif
