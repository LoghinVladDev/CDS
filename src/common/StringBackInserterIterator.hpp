//
// Created by loghin on 12/11/24.
//

#if defined(CDS_PRIMITIVE_STRING_BASE_HPP) && defined(CDS_ITERATOR_BACK_INSERTER_ITERATOR_HPP) \
    && !defined(CDS_COMMON_STRING_BACK_INSERTER_ITERATOR_HPP)
#define CDS_COMMON_STRING_BACK_INSERTER_ITERATOR_HPP

namespace cds {
namespace iterator {
namespace impl {
template <typename C, typename U, typename A> class BackInserterIterator<cds::impl::BaseString<C, U, A>> {
  using S = cds::impl::BaseString<C, U, A>;
public:
  CDS_ATTR(2(explicit, constexpr(11))) BackInserterIterator(S& obj) : _obj{obj} {}

  CDS_ATTR(constexpr(14)) auto operator=(BackInserterIterator const&) noexcept -> BackInserterIterator& {
    return *this;
  }

  template <typename V, EnableIf<Not<IsSame<RemoveCVRef<V>, BackInserterIterator>>> = 0>
  CDS_ATTR(constexpr(14)) auto operator=(V&& value) noexcept -> BackInserterIterator& {
    _obj += cds::impl::fwd<V>(value);
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator*() noexcept -> BackInserterIterator& {
    return *this;
  }

  CDS_ATTR(constexpr(14)) auto operator++() -> BackInserterIterator& {
    return *this;
  }

private:
  S& _obj;
};
} // namespace impl
} // namespace iterator
} // namespace cds

#endif // #if defined(CDS_PRIMITIVE_STRING_BASE_HPP) && defined(CDS_ITERATOR_BACK_INSERTER_ITERATOR_HPP)
       //     && !defined(CDS_COMMON_STRING_BACK_INSERTER_ITERATOR_HPP)
