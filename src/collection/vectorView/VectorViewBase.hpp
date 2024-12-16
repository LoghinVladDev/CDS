//
// Created by loghin on 12/16/24.
//

#ifndef CDS_COLLECTION_VECTOR_VIEW_BASE_HPP
#define CDS_COLLECTION_VECTOR_VIEW_BASE_HPP
#pragma once

#include <cassert>

namespace cds {
namespace impl {
template <typename T, typename B> class VectorViewBase : public B {
  using Base = B;

public:
  using Base::Base;
  using Base::begin;
  using Base::empty;
  using Base::end;
  using Base::first;
  using Base::last;
  using Base::size;
  using Base::sub;
  using Base::operator=;

  CDS_ATTR(3(nodiscard, explicit, constexpr(11))) operator bool() const noexcept {
    return !empty();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator[](Size index) const noexcept -> T& {
    assert(index < size() && "Accessing invalid index of view");
    return *(begin() + index);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto at(Size index) const noexcept -> T& {
    assert(index < size() && "Accessing invalid index of view");
    return *(begin() + index);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const noexcept -> T* {
    return begin().address();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto first(Size count) const noexcept -> VectorView<T> {
    assert(count <= size() && "Attempted to get first N elements where N is greater than extent of view");
    return VectorView<T>{begin(), begin() + count};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto last(Size count) const noexcept -> VectorView<T> {
    assert(count <= size() && "Attempted to get first N elements where N is greater than extent of view");
    return VectorView<T>{begin() + (size() - count), begin() + size()};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto sub(Size offset, Size count) const noexcept -> VectorView<T> {
    assert(offset + count <= size() && "Attempted to get first N elements where N is greater than extent of view");
    return VectorView<T>{begin() + offset, begin() + offset + count};
  }
};
} // namespace impl
} // namespace cds

#endif // CDS_COLLECTION_VECTOR_VIEW_BASE_HPP
