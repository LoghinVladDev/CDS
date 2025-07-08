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
using meta::RemoveConst;
using meta::impl::IsBaseOfIntrusiveICVR;

using iterator::ForwardAddressIterator;
using iterator::BackwardAddressIterator;

template <typename, Size> class BaseStaticVectorViewDefaultConstructorConstraint {
public:
  BaseStaticVectorViewDefaultConstructorConstraint() = delete;
  CDS_ATTR(2(explicit, constexpr(11))) BaseStaticVectorViewDefaultConstructorConstraint(int) noexcept {}
  BaseStaticVectorViewDefaultConstructorConstraint(BaseStaticVectorViewDefaultConstructorConstraint const&) = default;
  BaseStaticVectorViewDefaultConstructorConstraint(BaseStaticVectorViewDefaultConstructorConstraint&&) = default;
  auto operator=(BaseStaticVectorViewDefaultConstructorConstraint const&)
      -> BaseStaticVectorViewDefaultConstructorConstraint& = default;
  auto operator=(BaseStaticVectorViewDefaultConstructorConstraint&&)
      -> BaseStaticVectorViewDefaultConstructorConstraint& = default;
  ~BaseStaticVectorViewDefaultConstructorConstraint() = default;
};

template <typename T> class BaseStaticVectorViewDefaultConstructorConstraint<T, 0u> {
public:
  BaseStaticVectorViewDefaultConstructorConstraint() = default;
  CDS_ATTR(2(explicit, constexpr(11))) BaseStaticVectorViewDefaultConstructorConstraint(int) noexcept {}
  BaseStaticVectorViewDefaultConstructorConstraint(BaseStaticVectorViewDefaultConstructorConstraint const&) = default;
  BaseStaticVectorViewDefaultConstructorConstraint(BaseStaticVectorViewDefaultConstructorConstraint&&) = default;
  auto operator=(BaseStaticVectorViewDefaultConstructorConstraint const&)
      -> BaseStaticVectorViewDefaultConstructorConstraint& = default;
  auto operator=(BaseStaticVectorViewDefaultConstructorConstraint&&)
      -> BaseStaticVectorViewDefaultConstructorConstraint& = default;
  ~BaseStaticVectorViewDefaultConstructorConstraint() = default;
};

template <typename T, Size extent> class BaseStaticVectorView :
    public BaseStaticVectorViewDefaultConstructorConstraint<T, extent> {
public:
  using Iterator = ForwardAddressIterator<T>;
  using ConstIterator = ForwardAddressIterator<T const>;
  using ReverseIterator = BackwardAddressIterator<T>;
  using ConstReverseIterator = BackwardAddressIterator<T const>;

  template <typename It, EnableIf<IsRandomAccessIterator<It>> = 0> CDS_ATTR(2(explicit, constexpr(11)))
  BaseStaticVectorView(It first, Size const count) noexcept :
      BaseStaticVectorViewDefaultConstructorConstraint<T, extent>{0}, _addr{&*first} {
#if CDS_ATTR(cpp14)
    assert(count >= extent && "Static Vector View used on iterator count smaller than requested extent");
#endif
  }

  template <typename It, typename S, EnableIf<IsRandomAccessIterator<It, S>> = 0> CDS_ATTR(2(explicit, constexpr(11)))
  BaseStaticVectorView(It first, S end) noexcept : BaseStaticVectorView(first, static_cast<Size>(end - first)) {}

  template <typename C, EnableIf<And<
      VectorViewConversion<C>,
      Not<IsSame<RemoveCVRef<C>, BaseStaticVectorView>>,
      Not<IsBaseOfIntrusiveICVR<BaseStaticVectorView, C>>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) BaseStaticVectorView(C&& range) noexcept : BaseStaticVectorView{
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
  BaseStaticVectorView(BaseVector<T, E0, A0, S0>& vec) noexcept : BaseStaticVectorView{vec.begin(), vec.end()} {}

  template <
      typename E0, typename A0, typename S0, typename T0, typename T1 = T,
      EnableIf<And<IsConst<T1>, IsSame<RemoveConst<T1>, T0>>> = 0
  > CDS_ATTR(2(explicit, constexpr(11))) BaseStaticVectorView(BaseVector<T0, E0, A0, S0> const& vec) noexcept :
      BaseStaticVectorView{vec.begin(), vec.end()} {}

  BaseStaticVectorView() = default;
  BaseStaticVectorView(BaseStaticVectorView const&) = default;
  BaseStaticVectorView(BaseStaticVectorView&&) = default;
  auto operator=(BaseStaticVectorView const&) -> BaseStaticVectorView& = default;
  auto operator=(BaseStaticVectorView&&) -> BaseStaticVectorView& = default;
  ~BaseStaticVectorView() = default;

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
