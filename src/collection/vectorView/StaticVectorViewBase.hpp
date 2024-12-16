//
// Created by loghin on 12/16/24.
//

#ifndef CDS_COLLECTION_STATIC_VECTOR_VIEW_BASE_HPP
#define CDS_COLLECTION_STATIC_VECTOR_VIEW_BASE_HPP
#pragma once

#include <cassert>
#include <cds/iterator/AddressIterator>
#include "VectorViewConversion.hpp"

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Not;
using meta::IsConst;
using meta::IsRandomAccessIterator;
using meta::IsSame;
using meta::IsBaseOf;

using iterator::ForwardAddressIterator;
using iterator::BackwardAddressIterator;

template <typename, Size> class StaticVectorViewBaseDefaultConstructorConstraint {
public:
  StaticVectorViewBaseDefaultConstructorConstraint() = delete;
  CDS_ATTR(2(explicit, constexpr(11))) StaticVectorViewBaseDefaultConstructorConstraint(int) noexcept {}
  StaticVectorViewBaseDefaultConstructorConstraint(StaticVectorViewBaseDefaultConstructorConstraint const&) = default;
  StaticVectorViewBaseDefaultConstructorConstraint(StaticVectorViewBaseDefaultConstructorConstraint&&) = default;
  auto operator=(StaticVectorViewBaseDefaultConstructorConstraint const&)
      -> StaticVectorViewBaseDefaultConstructorConstraint& = default;
  auto operator=(StaticVectorViewBaseDefaultConstructorConstraint&&)
      -> StaticVectorViewBaseDefaultConstructorConstraint& = default;
  ~StaticVectorViewBaseDefaultConstructorConstraint() = default;
};

template <typename T> class StaticVectorViewBaseDefaultConstructorConstraint<T, 0u> {
public:
  StaticVectorViewBaseDefaultConstructorConstraint() = default;
  CDS_ATTR(2(explicit, constexpr(11))) StaticVectorViewBaseDefaultConstructorConstraint(int) noexcept {}
  StaticVectorViewBaseDefaultConstructorConstraint(StaticVectorViewBaseDefaultConstructorConstraint const&) = default;
  StaticVectorViewBaseDefaultConstructorConstraint(StaticVectorViewBaseDefaultConstructorConstraint&&) = default;
  auto operator=(StaticVectorViewBaseDefaultConstructorConstraint const&)
      -> StaticVectorViewBaseDefaultConstructorConstraint& = default;
  auto operator=(StaticVectorViewBaseDefaultConstructorConstraint&&)
      -> StaticVectorViewBaseDefaultConstructorConstraint& = default;
  ~StaticVectorViewBaseDefaultConstructorConstraint() = default;
};

template <typename T, Size extent> class StaticVectorViewBase :
    public StaticVectorViewBaseDefaultConstructorConstraint<T, extent> {
public:
  using Iterator = ForwardAddressIterator<T>;
  using ConstIterator = ForwardAddressIterator<T const>;
  using ReverseIterator = BackwardAddressIterator<T>;
  using ConstReverseIterator = BackwardAddressIterator<T const>;

  template <typename It, EnableIf<IsRandomAccessIterator<It>> = 0> CDS_ATTR(2(explicit, constexpr(11)))
  StaticVectorViewBase(It first, Size count) noexcept :
      StaticVectorViewBaseDefaultConstructorConstraint<T, extent>{0}, _addr{&*first} {
#if CDS_ATTR(cpp14)
    assert(count >= extent && "Static Vector View used on iterator count smaller than requested extent");
#endif
  }

  template <typename It, typename S, EnableIf<IsRandomAccessIterator<It, S>> = 0> CDS_ATTR(2(explicit, constexpr(11)))
  StaticVectorViewBase(It first, S end) noexcept : StaticVectorViewBase(first, end - first) {}

  template <typename C, EnableIf<And<
      VectorViewConversion<C>,
      Not<IsSame<RemoveCVRef<C>, StaticVectorViewBase>>,
      Not<IsBaseOf<StaticVectorViewBase, RemoveCVRef<C>>>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) StaticVectorViewBase(C&& range) noexcept : StaticVectorViewBase{
      VectorViewConversion<C>::begin(fwd<C>(range)),
      VectorViewConversion<C>::end(fwd<C>(range))
  } {
    static_assert(VectorViewConversion<C>::template ctAccepts<extent>(),
        "Extent of the view exceeds the known capacity of the received range");
#if CDS_ATTR(cpp14)
    assert(VectorViewConversion<C>::template accepts<extent>(fwd<C>(range))
           && "Extent of the view exceeds the known capacity of the received range");
#endif
  }

  template <typename E0, typename A0, typename S0> CDS_ATTR(2(explicit, constexpr(11)))
  StaticVectorViewBase(BaseVector<T, E0, A0, S0>& vec) noexcept : StaticVectorViewBase{vec.begin(), vec.end()} {}

  template <typename E0, typename A0, typename S0, typename T0 = T, EnableIf<IsConst<T0>>>
  CDS_ATTR(2(explicit, constexpr(11))) StaticVectorViewBase(BaseVector<T, E0, A0, S0> const& vec) noexcept :
      StaticVectorViewBase{vec.begin(), vec.end()} {}

  StaticVectorViewBase() = default;
  StaticVectorViewBase(StaticVectorViewBase const&) = default;
  StaticVectorViewBase(StaticVectorViewBase&&) = default;
  auto operator=(StaticVectorViewBase const&) -> StaticVectorViewBase& = default;
  auto operator=(StaticVectorViewBase&&) -> StaticVectorViewBase& = default;
  ~StaticVectorViewBase() = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> Iterator {
    return _addr;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin() const noexcept -> ConstIterator {
    return _addr;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Iterator {
    return _addr + extent;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cend() const noexcept -> ConstIterator {
    return _addr + extent;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin() const noexcept -> ReverseIterator {
    return _addr + extent;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin() const noexcept -> ConstReverseIterator {
    return _addr + extent;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rend() const noexcept -> ReverseIterator {
    return _addr;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crend() const noexcept -> ConstReverseIterator {
    return _addr;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return extent;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto empty() const noexcept -> Size {
    return extent == 0u;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto front() const noexcept -> T& {
    static_assert(extent != 0u, "Accessing front of empty view");
    return *begin();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto back() const noexcept -> T& {
    static_assert(extent != 0u, "Accessing back of empty view");
    return *(end() - 1);
  }

  template <Size count> CDS_ATTR(2(nodiscard, constexpr(11))) auto first() const noexcept
      -> VectorView<T, count> {
    static_assert(count <= extent, "Attempted to get first N elements where N is greater than extent of view");
    return VectorView<T, count>{_addr, _addr + count};
  }

  template <Size count> CDS_ATTR(2(nodiscard, constexpr(11))) auto last() const noexcept
      -> VectorView<T, count> {
    static_assert(count <= extent, "Attempted to get last N elements where N is greater than extent of view");
    return VectorView<T, count>{_addr + (extent - count), _addr + extent};
  }

  template <Size offset, Size count> CDS_ATTR(2(nodiscard, constexpr(11))) auto sub() const noexcept
      -> VectorView<T, count> {
    static_assert(offset + count <= extent,
        "Attempted to get sub of N elements where N + offset is greater than extent of view");
    return VectorView<T, count>{_addr + offset, _addr + offset + count};
  }

private:
  T* _addr{nullptr};
};
} // namespace impl
} // namespace cds

#endif // CDS_COLLECTION_STATIC_VECTOR_VIEW_BASE_HPP
