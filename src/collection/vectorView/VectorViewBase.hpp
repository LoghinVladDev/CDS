//
// Created by loghin on 12/16/24.
//

#ifndef CDS_COLLECTION_VECTOR_VIEW_BASE_HPP
#define CDS_COLLECTION_VECTOR_VIEW_BASE_HPP
#pragma once

#include <cds/meta/Base>

#include <cassert>

#include "../../stdlib/ostream.hpp"

namespace cds {
namespace impl {
using meta::rvalue;

template <typename T, typename B> class BaseVectorView : public B {
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

template <typename C, typename T, typename B>
CDS_ATTR(inline) auto operator<<(std::basic_ostream<C>& out, BaseVectorView<T, B> const& view)
    CDS_ATTR(noexcept(noexcept(out << rvalue<T>()))) -> std::basic_ostream<C>& {
  out << static_cast<C>('[');
  auto it = view.begin();
  auto end = view.end();
  if (it == end) {
    out << static_cast<C>(']');
    return out;
  }

  out << *it;
  for (++it; it != end; ++it) {
    out << static_cast<C>(',') << static_cast<C>(' ') << *it;
  }
  out << static_cast<C>(']');
  return out;
}

template <typename T, typename B0, typename B1> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    BaseVectorView<T, B0> const& lhs,
    BaseVectorView<T, B1> const& rhs
) noexcept -> bool {
  if (&lhs == &rhs) {
    return true;
  }

  if (lhs.size() != rhs.size()) {
    return false;
  }

  return cds::impl::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T, typename B0, typename B1> CDS_ATTR(inline) auto operator!=(
    BaseVectorView<T, B0> const& lhs,
    BaseVectorView<T, B1> const& rhs
) noexcept -> bool {
  if (&lhs == &rhs) {
    return false;
  }

  if (lhs.size() != rhs.size()) {
    return true;
  }

  return !cds::impl::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
} // namespace impl
} // namespace cds

#endif // CDS_COLLECTION_VECTOR_VIEW_BASE_HPP
