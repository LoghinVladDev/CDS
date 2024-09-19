//
// Created by loghin on 5/14/24.
//

#ifndef CDS_PRIMITIVE_UNION_HPP
#define CDS_PRIMITIVE_UNION_HPP
#pragma once

#include "union/UnionNode.hpp"

CDS_ATTR(disable_warning(gcc, "-Wterminate"))
CDS_ATTR(disable_warning(msvc, 4297))

namespace cds {
namespace impl {
using meta::inConstexpr;
using meta::lvalue;

template <typename... Types> class Union : private UnionStorageBase<Pack<Types...>> {
  using Base = UnionStorageBase<Pack<Types...>>;
  using Base::_idx;
  using Base::_data;

public:
  using Base::Base;
  using Base::operator=;
  Union() = default;
  Union(Union const&) = default;
  Union(Union&&) = default;
  auto operator=(Union const&) -> Union& = default;
  auto operator=(Union&&) -> Union& = default;
  using Base::valueless;
  using Base::emplace;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto index() const noexcept -> Size {
    return _idx;
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto is() const noexcept -> bool {
    return _idx == IndexOfBestMatch<T, Types...>::Type::value;
  }

  template <typename T, typename C> CDS_ATTR(constexpr(14)) auto ifIs(C&& callable) const CDS_ATTR(noexcept(noexcept(
      functional::invoke(
          cds::forward<C>(callable), lvalue<typename UnionBestMatch<T, Types...>::Type const&>()
      )
  ))) -> void /* Consider Optional<meta::InvokeReturnOf<C, typename impl::UnionBestMatch<T, Types...>::Type const&>>*/ {
    if (is<T>()) {
      functional::invoke(cds::forward<C>(callable), get<T>());
    }
  }

  template <typename T, typename C> CDS_ATTR(constexpr(14)) auto ifIs(C&& callable) CDS_ATTR(noexcept(noexcept(
      functional::invoke(
          cds::forward<C>(callable), lvalue<typename UnionBestMatch<T, Types...>::Type&>()
      )
  ))) -> void /* Consider Optional<meta::InvokeReturnOf<C, typename impl::UnionBestMatch<T, Types...>::Type const&>>*/ {
    if (is<T>()) {
      functional::invoke(cds::forward<C>(callable), get<T>());
    }
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(14))) auto get() const CDS_ATTR(noexcept(false))
      -> typename UnionBestMatch<T, Types...>::Type const& {
    if (!inConstexpr() && IndexOfBestMatch<T, Types...>::Type::value != _idx) {
      _data.template raise<T>(_idx);
    }
    return unionGet<typename UnionBestMatch<T, Types...>::Type>(_data);
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(14))) auto get() CDS_ATTR(noexcept(false))
      -> typename UnionBestMatch<T, Types...>::Type& {
    if (!inConstexpr() && IndexOfBestMatch<T, Types...>::Type::value != _idx) {
      _data.template raise<T>(_idx);
    }
    return unionGet<typename UnionBestMatch<T, Types...>::Type>(_data);
  }
};

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(11))) auto get(Union<Ts...> const& u)
    CDS_ATTR(noexcept(false)) -> typename UnionBestMatch<T, Ts...>::Type const& {
  return u.template get<T>();
}

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Union<Ts...>& u)
    CDS_ATTR(noexcept(false)) -> typename UnionBestMatch<T, Ts...>::Type& {
  return u.template get<T>();
}

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Union<Ts...>&& u)
    CDS_ATTR(noexcept(false)) -> typename UnionBestMatch<T, Ts...>::Type&& {
  return std::move(u.template get<T>());
}
} // namespace impl
} // namespace cds

namespace cds {
using impl::Union;
} // namespace cds

CDS_ATTR(enable_warning(gcc, "-Wterminate"))
CDS_ATTR(enable_warning(msvc, 4297))

#endif // #ifndef CDS_PRIMITIVE_UNION_HPP
