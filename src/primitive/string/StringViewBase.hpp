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

#include "../../bindings/BindingSelectors.hpp"
#include "../../bindings/static/ContainsOfStaticBinding.hpp"
#include "../../bindings/static/FindOfStaticBinding.hpp"

#include "StringUtils.hpp"

namespace cds {
class Allocator;
namespace impl {
using meta::StringTraits;

template <typename C, typename U = StringUtils<C, StringTraits<C>>, typename A = Allocator> class BaseString {};
template<typename C, typename U = StringUtils<C, StringTraits<C>>> class BaseStringView;
}

namespace meta {
template <typename C, typename U> struct IterableTraits<cds::impl::BaseStringView<C, U>> {
  using Value = C;
  using Iterator = iterator::ForwardAddressIterator<C const>;
  using ConstIterator = Iterator;
  using ReverseIterator = iterator::BackwardAddressIterator<C const>;
  using ConstReverseIterator = ReverseIterator;
};
}

namespace impl {
using sel::With;
using sel::Value;
using sel::Selector;
using sel::Forward;
using sel::Backward;
using sel::Immutable;

using meta::IterableTraits;
using meta::EnableIf;
using meta::Not;
using meta::IsSame;
using meta::Decay;
using meta::IsIntegral;
using meta::All;
using meta::IsConstructible;
using meta::IsBaseOf;

using meta::impl::IsIterator;
using meta::impl::IsReverseIterator;

#if CDS_ATTR(spaceship)
using std::strong_ordering;
#endif

template <typename C, typename U> class CDS_ATTR(inheritsEBOs) BaseStringView :
    public IterableTraits<BaseStringView<C, U>>,
    public ContainsOfStaticBinding<BaseStringView<C, U>, With<Value, Selector>>,
    public FindOfStaticBinding<BaseStringView<C, U>, With<Value, Selector, Forward, Backward, Immutable>> {
public:
  using ITraits = IterableTraits<BaseStringView<C, U>>;
  using typename ITraits::Value;
  using typename ITraits::Iterator;
  using typename ITraits::ConstIterator;
  using typename ITraits::ReverseIterator;
  using typename ITraits::ConstReverseIterator;
  using Address = C const*;

  static Idx const npos;
  static Idx const invalidIndex;

  CDS_ATTR(constexpr(11)) BaseStringView() noexcept = default;
  CDS_ATTR(constexpr(11)) BaseStringView(BaseStringView const&) noexcept = default;
  CDS_ATTR(constexpr(11)) BaseStringView(BaseStringView &&) noexcept = default;
  CDS_ATTR(constexpr(20)) ~BaseStringView() noexcept = default;

  template <typename AddressLike, EnableIf<Not<IsSame<Decay<AddressLike>, BaseStringView>>> = 0>
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

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator[](N idx) const noexcept -> Value {
    return _data[idx];
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto at(N idx) const noexcept -> Value {
    return _data[idx];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto front() const noexcept -> Value {
    return _data[0u];
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto back() const noexcept -> Value {
    return _data[_length - 1u];
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto sub(N from) const noexcept -> BaseStringView {
    return sub(from, -1);
  }

  template <typename N, EnableIf<IsIntegral<N>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(N from) const noexcept -> BaseStringView {
    return sub(from, -1);
  }

  template <typename N1, typename N2, EnableIf<All<IsIntegral, N1, N2>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(N1 from, N2 until) const noexcept -> BaseStringView {
    return sub(from, until);
  }

  template <typename N1, typename N2, EnableIf<All<IsIntegral, N1, N2>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto sub(N1 from, N2 until) const noexcept -> BaseStringView {
    Size sUntil;
    auto sFrom = static_cast<Size>(from);
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

  CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(Value character) const noexcept -> Idx {
    for (decltype(_length) idx = 0u; idx < _length; ++idx) {
      if (_data[idx] == character) {
        return idx;
      }
    }
    return npos;
  }

  template <typename S> CDS_ATTR(2(nodiscard, constexpr(14))) auto findFirst(
      Value character, S&& selector
  ) const noexcept -> Idx {
    for (decltype(_length) idx = 0u; idx < _length; ++idx) {
      if (cds::forward<S>(selector)(_data[idx]) == character) {
        return idx;
      }
    }
    return npos;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(Value character) const noexcept -> Idx {
    for (decltype(_length) idx = _length - 1u; idx >= 0; --idx) {
      if (_data[idx] == character) {
        return idx;
      }
    }
    return npos;
  }

  template <typename S> CDS_ATTR(2(nodiscard, constexpr(14))) auto findLast(
      Value character, S&& selector
  ) const noexcept -> Idx {
    for (decltype(_length) idx = _length - 1u; idx >= 0; --idx) {
      if (cds::forward<S>(selector)(_data[idx]) == character) {
        return idx;
      }
    }
    return npos;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(Value character) const noexcept -> bool {
    return findFirst(character) != npos;
  }

  template <typename S> CDS_ATTR(2(nodiscard, constexpr(14))) auto contains(
      Value character, S&& selector
  ) const noexcept -> bool {
    return findFirst(character, cds::forward<S>(selector)) != npos;
  }

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
  ) noexcept -> strong_ordering;
#endif

  template <typename A = Allocator> CDS_ATTR(2(nodiscard, constexpr(20)))
  auto str() const CDS_ATTR(noexcept(false)) -> BaseString<C, U, A>;

private:
  Address _data {nullptr};
  Size _length {0u};
};

template <typename C, typename U> Idx const BaseStringView<C, U>::npos = -1;
template <typename C, typename U> Idx const BaseStringView<C, U>::invalidIndex = BaseStringView<C, U>::npos;

template <typename C, typename U>
template <typename AddressLike, EnableIf<Not<IsSame<Decay<AddressLike>, BaseStringView<C, U>>>>>
CDS_ATTR(constexpr(11)) BaseStringView<C, U>::BaseStringView(AddressLike &&string) noexcept :
    _data(string),
    _length(U::length(cds::forward<AddressLike>(string))) {}

template <typename C, typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto operator==(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return U::compare(lhs._data, lhs._length, rhs._data, rhs._length) == U::Ordering::Equal;
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs == BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
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

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs != BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
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

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs < BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
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

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs > BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
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

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
  return lhs <= BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
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

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> bool {
return lhs >= BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator>=(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> bool {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) >= rhs;
}

#if CDS_ATTR(spaceship)
template <typename C, typename U> CDS_ATTR(constexpr(14)) auto operator<=>(
    BaseStringView<C, U> const& lhs, BaseStringView<C, U> const& rhs
) noexcept -> strong_ordering {
  if (lhs._data == rhs._data && lhs._length == rhs._length) {
    return strong_ordering::equivalent;
  }

  auto compareResult = U::compare(lhs._data, lhs._length, rhs._data, rhs._length);
  if (compareResult == U::Ordering::Greater) { return strong_ordering::greater; }
  if (compareResult == U::Ordering::Less) { return strong_ordering::less; }
  return strong_ordering::equal;
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    BaseStringView<C, U> const& lhs, T&& rhs
) noexcept -> strong_ordering {
  return lhs <=> BaseStringView<C, U>(cds::forward<T>(rhs));
}

template <typename C, typename U, typename T, EnableIf<And<
    IsConstructible<BaseStringView<C, U>, T>,
    Not<IsBaseOf<BaseStringView<C, U>, Decay<T>>>
>> = 0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator<=>(
    T&& lhs, BaseStringView<C, U> const& rhs
) noexcept -> strong_ordering {
  return BaseStringView<C, U>(cds::forward<T>(lhs)) <=> rhs;
}
#endif

template <typename C, typename U> struct FindOfResultMappingTraits<BaseStringView<C, U>> {
  template <typename T, EnableIf<IsIterator<T>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) static auto adapt(BaseStringView<C, U> const& string, T&& iterator) -> Idx {
    return end(string) == cds::forward<T>(iterator)
        ? BaseStringView<C, U>::npos
        : (cds::forward<T>(iterator) - begin(string));
  }

  template <typename T, EnableIf<IsReverseIterator<T>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) static auto adapt(BaseStringView<C, U> const& string, T&& iterator) -> Idx {
    return rend(string) == cds::forward<T>(iterator)
        ? BaseStringView<C, U>::npos
        : (string.length() - (cds::forward<T>(iterator) - rbegin(string) + 1));
  }
};

template <typename C, typename U> struct FindStringTransformer {
  template <typename IB, typename IE, typename I>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(IB&& b, IE&& e, I&& i) const noexcept -> Idx {
    return cds::forward<IE>(e) == cds::forward<I>(i)
        ? BaseStringView<C, U>::npos
        : (cds::forward<I>(i) - cds::forward<IB>(b));
  }
};

//template <typename C, typename U> CDS_ATTR(constexpr(14)) auto findFirstA(BaseStringView<C, U> const& sv, C value)
//noexcept -> Idx {
//  return findFirst(sv, value, FindStringTransformer<C, U>());
//}
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_STRING_VIEW_BASE_HPP
