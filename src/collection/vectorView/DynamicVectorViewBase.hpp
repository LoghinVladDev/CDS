//
// Created by loghin on 12/16/24.
//

#ifndef CDS_COLLECTION_DYNAMIC_VECTOR_VIEW_BASE_HPP
#define CDS_COLLECTION_DYNAMIC_VECTOR_VIEW_BASE_HPP
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

template <typename T> class BaseDynamicVectorView {
public:
  using Iterator = ForwardAddressIterator<T>;
  using ConstIterator = ForwardAddressIterator<T const>;
  using ReverseIterator = BackwardAddressIterator<T>;
  using ConstReverseIterator = BackwardAddressIterator<T const>;

  template <typename It, EnableIf<IsRandomAccessIterator<It>> = 0> CDS_ATTR(2(explicit, constexpr(11)))
  BaseDynamicVectorView(It first, Size const count) noexcept : _begin{&*first}, _end{_begin + count} {}

  template <typename It, typename S, EnableIf<IsRandomAccessIterator<It, S>> = 0> CDS_ATTR(2(explicit, constexpr(11)))
  BaseDynamicVectorView(It first, S end) noexcept : BaseDynamicVectorView(first, static_cast<Size>(end - first)) {}

  template <typename C, EnableIf<And<
      VectorViewConversion<C>,
      Not<IsSame<RemoveCVRef<C>, BaseDynamicVectorView>>,
      Not<IsBaseOfIntrusiveICVR<BaseDynamicVectorView, C>>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) BaseDynamicVectorView(C&& range) noexcept : BaseDynamicVectorView{
      VectorViewConversion<C>::begin(fwd<C>(range)),
      VectorViewConversion<C>::end(fwd<C>(range))
  } {}

  template <typename E0, typename A0, typename S0> CDS_ATTR(2(implicit, constexpr(11)))
  BaseDynamicVectorView(BaseVector<T, E0, A0, S0>& vec) noexcept : BaseDynamicVectorView{vec.begin(), vec.end()} {}

  template <
      typename E0, typename A0, typename S0, typename T0, typename T1 = T,
      EnableIf<And<IsConst<T1>, IsSame<RemoveConst<T1>, T0>>> = 0
  > CDS_ATTR(2(implicit, constexpr(11))) BaseDynamicVectorView(BaseVector<T0, E0, A0, S0> const& vec) noexcept :
      BaseDynamicVectorView{vec.begin(), vec.end()} {}

  BaseDynamicVectorView() = default;
  BaseDynamicVectorView(BaseDynamicVectorView const&) = default;
  BaseDynamicVectorView(BaseDynamicVectorView&&) = default;
  auto operator=(BaseDynamicVectorView const&) -> BaseDynamicVectorView& = default;
  auto operator=(BaseDynamicVectorView&&) -> BaseDynamicVectorView& = default;
  ~BaseDynamicVectorView() = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> Iterator {
    return _begin;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin() const noexcept -> ConstIterator {
    return _begin;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Iterator {
    return _end;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cend() const noexcept -> ConstIterator {
    return _end;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin() const noexcept -> ReverseIterator {
    return _end;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin() const noexcept -> ConstReverseIterator {
    return _end;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rend() const noexcept -> ReverseIterator {
    return _begin;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crend() const noexcept -> ConstReverseIterator {
    return _begin;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return static_cast<Size>(_end - _begin);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto empty() const noexcept -> Size {
    return _begin == _end;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto front() const noexcept -> T& {
#if CDS_ATTR(cpp14)
    assert(!empty() && "Accessing front of empty view");
#endif
    return *begin();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto back() const noexcept -> T& {
#if CDS_ATTR(cpp14)
    assert(!empty() && "Accessing back of empty view");
#endif
    return *(end() - 1);
  }

  template <Size count> CDS_ATTR(2(nodiscard, constexpr(11))) auto first() const noexcept
      -> VectorView<T, count> {
    assert(count <= size() && "Attempted to get first N elements where N is greater than extent of view");
    return VectorView<T, count>{_begin, _begin + count};
  }

  template <Size count> CDS_ATTR(2(nodiscard, constexpr(11))) auto last() const noexcept
      -> VectorView<T, count> {
    assert(count <= size() && "Attempted to get last N elements where N is greater than extent of view");
    return VectorView<T, count>{_begin + (size() - count), _begin + size()};
  }

  template <Size offset, Size count> CDS_ATTR(2(nodiscard, constexpr(11))) auto sub() const noexcept
      -> VectorView<T, count> {
    assert(offset + count <= size()
        && "Attempted to get sub of N elements where N + offset is greater than extent of view");
    return VectorView<T, count>{_begin + offset, _begin + offset + count};
  }

private:
  T* _begin{nullptr};
  T* _end{nullptr};
};
} // namespace impl
} // namespace cds

#endif // CDS_COLLECTION_DYNAMIC_VECTOR_VIEW_BASE_HPP
