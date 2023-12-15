//
// Created by loghin on 12/8/23.
//

#ifndef CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
#define CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
#pragma once

#include <cds/Utility>
#include <cds/meta/StringTraits>
#include <cds/iterator/AddressIterator>
#include <cds/functional/FunctionalInterface>

#include "../../shared/bindings/static/ContainsOfStaticBinding.hpp"

#include "StringUtils.hpp"

namespace cds {
class Allocator;
template <
    typename C,
    typename U = impl::StringUtils<C, meta::StringTraits<C>>,
    typename A = Allocator
> class BaseString {};

namespace impl {
template <
    typename C,
    typename U = impl::StringUtils<C, meta::StringTraits<C>>
> class BaseStringView {
public:
  using Value = C;
  using Address = C const*;
  using Iterator = ForwardAddressIterator<C const>;
  using ConstIterator = Iterator;
  using ReverseIterator = BackwardAddressIterator<C const>;
  using ConstReverseIterator = ReverseIterator;

  CDS_ATTR(constexpr(11)) BaseStringView() noexcept = default;
  CDS_ATTR(constexpr(11)) BaseStringView(BaseStringView const&) noexcept = default;
  CDS_ATTR(constexpr(11)) BaseStringView(BaseStringView &&) noexcept = default;
  CDS_ATTR(constexpr(20)) ~BaseStringView() noexcept = default;

  template <typename AddressLike, meta::EnableIf<meta::Not<meta::IsSame<meta::Decay<AddressLike>, BaseStringView>>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) BaseStringView(AddressLike&& string) noexcept;
  CDS_ATTR(constexpr(11)) BaseStringView(Address data, Size length) noexcept : _data(data), _length(length) {}

  CDS_ATTR(constexpr(14)) auto operator=(BaseStringView const&) noexcept -> BaseStringView& = default;
  CDS_ATTR(constexpr(14)) auto operator=(BaseStringView&&) noexcept -> BaseStringView& = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const noexcept -> Address {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto length() const noexcept -> Size {
    return _length;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto size() const noexcept -> Size {
    return _length;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto empty() const noexcept -> bool {
    return _length == 0u;
  }

  CDS_ATTR(3(nodiscard, explicit, constexpr(11))) operator bool() const noexcept {
    return !empty();
  }

  CDS_ATTR(constexpr(14)) auto clear() noexcept -> void {
    _data = nullptr;
    _length = 0u;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> Iterator {
    return Iterator(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> Iterator {
    return Iterator(_data + _length);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin() const noexcept -> ConstIterator {
    return ConstIterator(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cend() const noexcept -> ConstIterator {
    return ConstIterator(_data + _length);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rbegin() const noexcept -> ReverseIterator {
    return ReverseIterator(_data + _length - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto rend() const noexcept -> ReverseIterator {
    return ReverseIterator(_data - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crbegin() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(_data + _length - 1);
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto crend() const noexcept -> ConstReverseIterator {
    return ConstReverseIterator(_data - 1);
  }

  template <typename N, meta::EnableIf<meta::IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator[](N idx) const noexcept -> Value {
    return _data[idx];
  }

  template <typename N, meta::EnableIf<meta::IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto at(N idx) const noexcept -> Value {
    return _data[idx];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto front() const noexcept -> Value {
    return _data[0u];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto back() const noexcept -> Value {
    return _data[_length - 1u];
  }

  template <typename N, meta::EnableIf<meta::IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto sub(N from) const noexcept -> BaseStringView {
    return sub(from, -1);
  }

  template <typename N, meta::EnableIf<meta::IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(N from) const noexcept -> BaseStringView {
    return sub(from, -1);
  }

  template <typename N1, typename N2, meta::EnableIf<meta::All<meta::IsIntegral, N1, N2>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(N1 from, N2 until) const noexcept -> BaseStringView {
    return sub(from, until);
  }

  template <typename N1, typename N2, meta::EnableIf<meta::All<meta::IsIntegral, N1, N2>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto sub(N1 from, N2 until) const noexcept -> BaseStringView {
    Size sUntil;
    Size sFrom = static_cast<Size>(from);
    if (until < 0) {
      sUntil = size();
    } else {
      sUntil = static_cast<Size>(until);
    }

    if (sFrom >= sUntil) {
      return {};
    }

    return {_data + sFrom, sUntil - sFrom};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(Value character) const noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator==(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator!=(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator<(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator>(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator<=(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator>=(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> bool;

#if CDS_ATTR(spaceship)
  template <typename FC, typename FU> CDS_ATTR(constexpr(14)) friend auto operator<=>(
      BaseStringView<FC, FU> const& lhs, BaseStringView<FC, FU> const& rhs
  ) noexcept -> std::strong_ordering;
#endif

  template <typename A = Allocator> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto str() const CDS_ATTR(noexcept(false)) -> BaseString<C, U, A>;

private:
  Address _data {nullptr};
  Size _length {0u};
};

template <typename C, typename U>
template <typename AddressLike, meta::EnableIf<meta::Not<meta::IsSame<meta::Decay<AddressLike>, BaseStringView<C, U>>>>>
CDS_ATTR(constexpr(11)) BaseStringView<C, U>::BaseStringView(AddressLike &&string) noexcept :
    _data(string),
    _length(U::length(cds::forward<AddressLike>(string))) {}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) == U::Ordering::Equal;
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs == BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) == rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator!=(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) != U::Ordering::Equal;
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs != BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) != rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator<(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) == U::Ordering::Less;
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs < BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) < rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator>(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) == U::Ordering::Greater;
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs > BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) > rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator<=(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) != U::Ordering::Greater;
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs <= BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) <= rhs;
}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator>=(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) != U::Ordering::Less;
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
return lhs >= BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) >= rhs;
}

#if CDS_ATTR(spaceship)
template <typename C, typename U> CDS_ATTR(constexpr(14)) auto operator<=>(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> std::strong_ordering {
  if (lhs._data == rhs._data && lhs._length == rhs._length) {
    return std::strong_ordering::equivalent;
  }

  auto compareResult = U::compare(lhs._data, lhs._length, rhs._data, rhs._length);
  if (compareResult == U::Ordering::Greater) { return std::strong_ordering::greater; }
  if (compareResult == U::Ordering::Less) { return std::strong_ordering::less; }
  return std::strong_ordering::equal;
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> std::strong_ordering {
  return lhs <=> BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, meta::EnableIf<meta::And<
    meta::IsConstructible<BaseStringView<C, U>, T>,
    meta::Not<meta::IsBaseOf<BaseStringView<C, U>, meta::Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> std::strong_ordering {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) <=> rhs;
}
#endif
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
