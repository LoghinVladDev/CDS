//
// Created by loghin on 12/8/23.
//

#ifndef CDS_ITERATOR_ADDRESS_ITERATOR_HPP
#define CDS_ITERATOR_ADDRESS_ITERATOR_HPP
#pragma once

#include <cds/meta/IteratorTraits>
#include <cds/meta/ObjectTraits>

#if CDS_ATTR(spaceship)
#include <compare>
#endif

namespace cds {
namespace impl {
template<typename T, bool fwd> class AddressIteratorBase {
public:
  using Value = T;
  using Address = T *;
  using Reference = T &;
  static constexpr bool forward = fwd;

  CDS_ATTR(constexpr(11)) AddressIteratorBase() noexcept = default;
  CDS_ATTR(constexpr(11)) AddressIteratorBase(AddressIteratorBase const &) noexcept = default;
  CDS_ATTR(constexpr(11)) AddressIteratorBase(AddressIteratorBase &&) noexcept = default;
  CDS_ATTR(2(implicit, constexpr(11))) AddressIteratorBase(Address address) noexcept: _addr(address) {}
  ~AddressIteratorBase() noexcept = default;

  CDS_ATTR(constexpr(14)) auto operator=(AddressIteratorBase const &) noexcept -> AddressIteratorBase & = default;
  CDS_ATTR(constexpr(14)) auto operator=(AddressIteratorBase &&) noexcept -> AddressIteratorBase & = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const noexcept -> Reference {
    return *_addr;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator->() const noexcept -> Address {
    return _addr;
  }

  template <typename N> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator[](N index) const noexcept -> Reference {
    return _addr[index];
  }

  template <typename Lhs, typename Rhs, bool fFwd> CDS_ATTR(constexpr(11)) friend auto operator==(
      AddressIteratorBase<Lhs, fFwd> const& lhs, AddressIteratorBase<Rhs, fFwd> const& rhs
  ) noexcept -> bool;

  template <typename Lhs, typename Rhs, bool fFwd> CDS_ATTR(constexpr(11)) friend auto operator!=(
      AddressIteratorBase<Lhs, fFwd> const& lhs, AddressIteratorBase<Rhs, fFwd> const& rhs
  ) noexcept -> bool;

  template <typename Lhs, typename Rhs> CDS_ATTR(constexpr(11)) friend auto operator<(
      AddressIteratorBase<Lhs, fwd> const& lhs, AddressIteratorBase<Rhs, fwd> const& rhs
  ) noexcept -> bool;

  template <typename Lhs, typename Rhs> CDS_ATTR(constexpr(11)) friend auto operator>(
      AddressIteratorBase<Lhs, fwd> const& lhs, AddressIteratorBase<Rhs, fwd> const& rhs
  ) noexcept -> bool;

  template <typename Lhs, typename Rhs> CDS_ATTR(constexpr(11)) friend auto operator<=(
      AddressIteratorBase<Lhs, fwd> const& lhs, AddressIteratorBase<Rhs, fwd> const& rhs
  ) noexcept -> bool;

  template <typename Lhs, typename Rhs> CDS_ATTR(constexpr(11)) friend auto operator>=(
      AddressIteratorBase<Lhs, fwd> const& lhs, AddressIteratorBase<Rhs, fwd> const& rhs
  ) noexcept -> bool;

#if CDS_ATTR(spaceship)
  template <typename Lhs, typename Rhs> CDS_ATTR(always_constexpr) friend auto operator<=>(
      AddressIteratorBase<Lhs, fwd> const& lhs, AddressIteratorBase<Rhs, fwd> const& rhs
  ) noexcept -> std::strong_ordering;
#endif

  template <typename Lhs, typename Rhs, bool fFwd> CDS_ATTR(constexpr(11)) friend auto operator-(
      AddressIteratorBase<Lhs, fFwd> const& lhs, AddressIteratorBase<Rhs, fFwd> const& rhs
  ) noexcept -> Size;

  template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, fwd>, I>>>
  CDS_ATTR(constexpr(14)) friend auto operator++(I& iterator) noexcept -> I&;

  template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, fwd>, I>>>
  CDS_ATTR(constexpr(14)) friend auto operator--(I& iterator) noexcept -> I&;

  template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, fwd>, I>>>
  CDS_ATTR(constexpr(14)) friend auto operator++(I& iterator, int _) noexcept -> I;

  template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, fwd>, I>>>
  CDS_ATTR(constexpr(14)) friend auto operator--(I& iterator, int _) noexcept -> I;

  template <typename I, typename N, typename meta::EnableIf<meta::And<
      meta::IsBaseOf<AddressIteratorBase<typename I::Value, fwd>, I>,
      meta::IsIntegral<N>
  >>> CDS_ATTR(constexpr(11)) friend auto operator+(
      I const& lhs, N rhs
  ) noexcept -> I;

  template <typename I, typename N, typename meta::EnableIf<meta::And<
      meta::IsBaseOf<AddressIteratorBase<typename I::Value, fwd>, I>,
      meta::IsIntegral<N>
  >>> CDS_ATTR(constexpr(11)) friend auto operator-(
      I const& lhs, N rhs
  ) noexcept -> I;

private:
  Address _addr{nullptr};
};

template <typename Lhs, typename Rhs, bool ordering> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    AddressIteratorBase<Lhs, ordering> const& lhs, AddressIteratorBase<Rhs, ordering> const& rhs
) noexcept -> bool {
  return lhs._addr == rhs._addr;
}

template <typename Lhs, typename Rhs, bool ordering> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    AddressIteratorBase<Lhs, ordering> const& lhs, AddressIteratorBase<Rhs, ordering> const& rhs
) noexcept -> bool {
  return lhs._addr != rhs._addr;
}

template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    AddressIteratorBase<Lhs, true> const& lhs, AddressIteratorBase<Rhs, true> const& rhs
) noexcept -> bool {
  return lhs._addr < rhs._addr;
}

template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    AddressIteratorBase<Lhs, false> const& lhs, AddressIteratorBase<Rhs, false> const& rhs
) noexcept -> bool {
  return lhs._addr > rhs._addr;
}

template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    AddressIteratorBase<Lhs, true> const& lhs, AddressIteratorBase<Rhs, true> const& rhs
) noexcept -> bool {
  return lhs._addr > rhs._addr;
}

template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    AddressIteratorBase<Lhs, false> const& lhs, AddressIteratorBase<Rhs, false> const& rhs
) noexcept -> bool {
  return lhs._addr < rhs._addr;
}

template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    AddressIteratorBase<Lhs, true> const& lhs, AddressIteratorBase<Rhs, true> const& rhs
) noexcept -> bool {
  return lhs._addr <= rhs._addr;
}

template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    AddressIteratorBase<Lhs, false> const& lhs, AddressIteratorBase<Rhs, false> const& rhs
) noexcept -> bool {
  return lhs._addr >= rhs._addr;
}

template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    AddressIteratorBase<Lhs, true> const& lhs, AddressIteratorBase<Rhs, true> const& rhs
) noexcept -> bool {
  return lhs._addr >= rhs._addr;
}

template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    AddressIteratorBase<Lhs, false> const& lhs, AddressIteratorBase<Rhs, false> const& rhs
) noexcept -> bool {
  return lhs._addr <= rhs._addr;
}

#if CDS_ATTR(spaceship)
template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, always_constexpr)) auto operator<=>(
    AddressIteratorBase<Lhs, true> const& lhs, AddressIteratorBase<Rhs, true> const& rhs
) noexcept -> std::strong_ordering {
  return lhs._addr <=> rhs._addr;
}

template <typename Lhs, typename Rhs> CDS_ATTR(2(nodiscard, always_constexpr)) auto operator<=>(
    AddressIteratorBase<Lhs, false> const& lhs, AddressIteratorBase<Rhs, false> const& rhs
) noexcept -> std::strong_ordering {
  if (lhs._addr < rhs._addr) {
    return std::strong_ordering::greater;
  }

  if (lhs._addr > rhs._addr) {
    return std::strong_ordering::less;
  }

  return std::strong_ordering::equal;
}
#endif

template <typename Lhs, typename Rhs, bool fwd> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator-(
    AddressIteratorBase<Lhs, fwd> const& lhs, AddressIteratorBase<Rhs, fwd> const& rhs
) noexcept -> Size {
  return lhs._addr > rhs._addr
      ? lhs._addr - rhs._addr
      : rhs._addr - lhs._addr;
}

template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, true>, I>> = 0>
CDS_ATTR(constexpr(14)) auto operator++(I& iterator) noexcept -> I& {
  ++(static_cast<AddressIteratorBase<typename I::Value, true>&>(iterator)._addr);
  return iterator;
}

template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, false>, I>> = 0>
CDS_ATTR(constexpr(14)) auto operator++(I& iterator) noexcept -> I& {
  --static_cast<AddressIteratorBase<typename I::Value, false>&>(iterator)._addr;
  return iterator;
}

template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, true>, I>> = 0>
CDS_ATTR(constexpr(14)) auto operator--(I& iterator) noexcept -> I& {
  --static_cast<AddressIteratorBase<typename I::Value, true>&>(iterator)._addr;
  return iterator;
}

template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, false>, I>> = 0>
CDS_ATTR(constexpr(14)) auto operator--(I& iterator) noexcept -> I& {
  ++static_cast<AddressIteratorBase<typename I::Value, false>&>(iterator)._addr;
  return iterator;
}

template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, true>, I>> = 0>
CDS_ATTR(constexpr(14)) auto operator++(I& iterator, int) noexcept -> I {
  I const copy = iterator;
  static_cast<AddressIteratorBase<typename I::Value, true>&>(iterator)._addr++;
  return copy;
}

template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, false>, I>> = 0>
CDS_ATTR(constexpr(14)) auto operator++(I& iterator, int) noexcept -> I {
  I const copy = iterator;
  static_cast<AddressIteratorBase<typename I::Value, false>&>(iterator)._addr--;
  return copy;
}

template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, true>, I>> = 0>
CDS_ATTR(constexpr(14)) auto operator--(I& iterator, int) noexcept -> I {
  I const copy = iterator;
  static_cast<AddressIteratorBase<typename I::Value, true>&>(iterator)._addr--;
  return copy;
}

template <typename I, typename meta::EnableIf<meta::IsBaseOf<AddressIteratorBase<typename I::Value, false>, I>> = 0>
CDS_ATTR(constexpr(14)) auto operator--(I& iterator, int) noexcept -> I {
  I const copy = iterator;
  static_cast<AddressIteratorBase<typename I::Value, false>&>(iterator)._addr++;
  return copy;
}

template <typename I, typename N, typename meta::EnableIf<meta::And<
    meta::IsBaseOf<AddressIteratorBase<typename I::Value, true>, I>,
    meta::IsIntegral<N>
>> = 0> CDS_ATTR(constexpr(11)) auto operator+(
    I const& lhs, N rhs
) noexcept -> I {
  return I(static_cast<AddressIteratorBase<typename I::Value, true> const&>(lhs)._addr + rhs);
}

template <typename I, typename N, typename meta::EnableIf<meta::And<
    meta::IsBaseOf<AddressIteratorBase<typename I::Value, false>, I>,
    meta::IsIntegral<N>
>> = 0> CDS_ATTR(constexpr(11)) auto operator+(
    I const& lhs, N rhs
) noexcept -> I {
  return I(static_cast<AddressIteratorBase<typename I::Value, false> const&>(lhs)._addr - rhs);
}

template <typename I, typename N, typename meta::EnableIf<meta::And<
    meta::IsBaseOf<AddressIteratorBase<typename I::Value, true>, I>,
    meta::IsIntegral<N>
>> = 0> CDS_ATTR(constexpr(11)) auto operator-(
    I const& lhs, N rhs
) noexcept -> I {
  return I(static_cast<AddressIteratorBase<typename I::Value, true> const&>(lhs)._addr - rhs);
}

template <typename I, typename N, typename meta::EnableIf<meta::And<
    meta::IsBaseOf<AddressIteratorBase<typename I::Value, false>, I>,
    meta::IsIntegral<N>
>> = 0> CDS_ATTR(constexpr(11)) auto operator-(
    I const& lhs, N rhs
) noexcept -> I {
  return I(static_cast<AddressIteratorBase<typename I::Value, false> const&>(lhs)._addr + rhs);
}
} // namespace impl

template <typename Type> class ForwardAddressIterator : public impl::AddressIteratorBase<Type, true> {
  using impl::AddressIteratorBase<Type, true>::AddressIteratorBase;
};

template <typename Type> class BackwardAddressIterator : public impl::AddressIteratorBase<Type, false> {
  using impl::AddressIteratorBase<Type, false>::AddressIteratorBase;
};

template <typename Type, Size size> CDS_ATTR(constexpr(11)) auto begin(Type (&array)[size]) -> ForwardAddressIterator<Type> {
  return {&array[0]};
}

template <typename Type, Size size> CDS_ATTR(constexpr(11)) auto end(Type (&array)[size]) -> ForwardAddressIterator<Type> {
  return {&array[size]};
}

template <typename Type, Size size> CDS_ATTR(constexpr(11)) auto cbegin(Type (&array)[size]) -> ForwardAddressIterator<Type const> {
  return {&array[0]};
}

template <typename Type, Size size> CDS_ATTR(constexpr(11)) auto cend(Type (&array)[size]) -> ForwardAddressIterator<Type const> {
  return {&array[size]};
}

template <typename Type, Size size> CDS_ATTR(constexpr(11)) auto rbegin(Type (&array)[size]) -> BackwardAddressIterator<Type> {
  return {&array[size] - 1};
}

template <typename Type, Size size> CDS_ATTR(constexpr(11)) auto rend(Type (&array)[size]) -> BackwardAddressIterator<Type> {
  return {&array[0] - 1};
}

template <typename Type, Size size> CDS_ATTR(constexpr(11)) auto crbegin(Type (&array)[size]) -> BackwardAddressIterator<Type const> {
  return {&array[size] - 1};
}

template <typename Type, Size size> CDS_ATTR(constexpr(11)) auto crend(Type (&array)[size]) -> BackwardAddressIterator<Type const> {
  return {&array[0] - 1};
}
} // namespace cds

#endif // CDS_ITERATOR_ADDRESS_ITERATOR_HPP
