//
// Created by loghin on 5/14/24.
//

#ifndef CDS_PRIMITIVE_UNION_HPP
#define CDS_PRIMITIVE_UNION_HPP
#pragma once

#include "union/UnionNode.hpp"

CDS_ATTR(disable_warning(gcc, "-Wterminate"))

namespace cds {
template <typename... Types> class Union {
  using Data = impl::UnionNode<0u, Types...>;

public:
  CDS_ATTR(constexpr(11)) Union() CDS_ATTR(noexcept(noexcept(Data()))) : _data{}, _idx{0u} {}
  CDS_ATTR(constexpr(14)) Union(Union const& obj)
      CDS_ATTR(noexcept(noexcept(meta::lvalue<Data>().copyConstruct(0u, obj._data)))) CDS_ATTR(try_list(
          _data(obj._idx, obj._data),
          _idx(sizeof...(Types))
      )) {
        _idx = obj._idx;
      } CDS_ATTR(catch(..., {
        throw;
      }))

  CDS_ATTR(constexpr(14)) Union(Union&& obj) CDS_ATTR(noexcept(noexcept(Data{obj._idx, cds::move(obj._data)}))) :
      _data{obj._idx, cds::move(obj._data)},
      _idx{obj._idx} {}

  template <typename Arg, meta::EnableIf<meta::Not<meta::IsSame<meta::RemoveCVRef<Arg>, Union>>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) Union(Arg&& arg)
      CDS_ATTR(noexcept(noexcept(Data(cds::forward<Arg>(arg))))) :
      _data{cds::forward<Arg>(arg)},
      _idx{impl::IndexOfBestMatch<Arg, Types...>::Type::value} {}

  CDS_ATTR(constexpr(20)) auto operator=(Union const& obj) CDS_ATTR(noexcept(
      noexcept(meta::lvalue<Data>().copyConstruct(0u, obj._data))
      && noexcept(meta::lvalue<Data>().copyAssign(0u, obj._data))
  )) -> Union& {
    if (this == &obj) {
      return *this;
    }

    CDS_ATTR(try) {
      if (_idx == obj._idx) {
        _data.copyAssign(_idx, obj._data);
      } else {
        _data.destruct(_idx);
        _idx = obj._idx;
        _data.copyConstruct(_idx, obj._data);
      }
      return *this;
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (Types);
      throw;
    }))
  }

  CDS_ATTR(constexpr(20)) auto operator=(Union&& obj) CDS_ATTR(noexcept(
      noexcept(meta::lvalue<Data>().moveConstruct(0u, cds::move(obj._data)))
      && noexcept(meta::lvalue<Data>().moveAssign(0u, cds::move(obj._data)))
  )) -> Union& {
    if (this == &obj) {
      return *this;
    }

    CDS_ATTR(try) {
      if (_idx == obj._idx) {
        _data.moveAssign(_idx, cds::move(obj._data));
      } else {
        _data.destruct(_idx);
        _idx = obj._idx;
        _data.moveConstruct(_idx, cds::move(obj._data));
      }
      return *this;
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (Types);
      throw;
    }))
  }

  template <typename Arg, meta::EnableIf<meta::Not<meta::IsSame<meta::RemoveCVRef<Arg>, Union>>> = 0>
  CDS_ATTR(constexpr(14)) auto operator=(Arg&& arg)
      CDS_ATTR(noexcept(noexcept(meta::lvalue<Data>()
        .template emplace<typename impl::UnionBestMatch<Arg, Types...>::Type>(cds::forward<Arg>(arg))
      ))) -> Union& {
    if (_idx != impl::IndexOfBestMatch<Arg, Types...>::Type::value && !valueless()) {
      _data.destruct(cds::exchange(_idx, sizeof... (Types)));
    }

    CDS_ATTR(try) {
      if (valueless()) {
        _data.template emplace<typename impl::UnionBestMatch<Arg, Types...>::Type>(cds::forward<Arg>(arg));
        _idx = impl::IndexOfBestMatch<Arg, Types...>::Type::value;
      } else {
        _data.set(cds::forward<Arg>(arg));
      }
    } CDS_ATTR(catch(..., {
      _idx = sizeof... (Types);
      throw;
    }))
    return *this;
  }

  template <typename T, typename... Args>
  CDS_ATTR(constexpr(14)) auto emplace(Args&&... args)
      CDS_ATTR(noexcept(noexcept(meta::lvalue<Data>()
        .template emplace<typename impl::UnionBestMatch<T, Types...>::Type>(cds::forward<Args>(args)...)
      )))
      -> typename impl::UnionBestMatch<T, Types...>::Type& {
    if (!valueless()) {
      _data.destruct(cds::exchange(_idx, sizeof... (Types)));
    }

    CDS_ATTR(try) {
      auto& value = _data
          .template emplace<typename impl::UnionBestMatch<T, Types...>::Type>(cds::forward<Args>(args)...);
      _idx = impl::IndexOfBestMatch<T, Types...>::Type::value;
      return value;
    } CDS_ATTR(catch(..., {
      throw;
    }))
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto index() const noexcept -> Size {
    return _idx;
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto is() const noexcept -> bool {
    return _idx == impl::IndexOfBestMatch<T, Types...>::Type::value;
  }

  template <typename T, typename C> CDS_ATTR(constexpr(14)) auto ifIs(C&& callable) const CDS_ATTR(noexcept(noexcept(
      functional::invoke(
          cds::forward<C>(callable), meta::lvalue<typename impl::UnionBestMatch<T, Types...>::Type const&>()
      )
  ))) -> void /* Consider Optional<meta::InvokeReturnOf<C, typename impl::UnionBestMatch<T, Types...>::Type const&>>*/ {
    if (is<T>()) {
      functional::invoke(cds::forward<C>(callable), get<T>());
    }
  }

  template <typename T, typename C> CDS_ATTR(constexpr(14)) auto ifIs(C&& callable) CDS_ATTR(noexcept(noexcept(
      functional::invoke(
          cds::forward<C>(callable), meta::lvalue<typename impl::UnionBestMatch<T, Types...>::Type&>()
      )
  ))) -> void /* Consider Optional<meta::InvokeReturnOf<C, typename impl::UnionBestMatch<T, Types...>::Type const&>>*/ {
    if (is<T>()) {
      functional::invoke(cds::forward<C>(callable), get<T>());
    }
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto valueless() const noexcept -> bool {
    return _idx == sizeof... (Types);
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(14))) auto get() const CDS_ATTR(noexcept(false))
      -> typename impl::UnionBestMatch<T, Types...>::Type const& {
    if (!meta::inConstexpr() && impl::IndexOfBestMatch<T, Types...>::Type::value != _idx) {
      _data.template raise<T>(_idx);
    }
    return impl::unionGet<typename impl::UnionBestMatch<T, Types...>::Type>(_data);
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(14))) auto get() CDS_ATTR(noexcept(false))
      -> typename impl::UnionBestMatch<T, Types...>::Type& {
    if (!meta::inConstexpr() && impl::IndexOfBestMatch<T, Types...>::Type::value != _idx) {
      _data.template raise<T>(_idx);
    }
    return impl::unionGet<typename impl::UnionBestMatch<T, Types...>::Type>(_data);
  }

  CDS_ATTR(constexpr(20)) ~Union() noexcept {
    _data.destruct(_idx);
  }

private:
  Data _data;
  Size _idx;
};

namespace impl {
template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Union<Ts...> const& u)
    CDS_ATTR(noexcept(false)) -> typename UnionBestMatch<T, Ts...>::Type const& {
  return u.template get<T>();
}

template <typename T, typename... Ts> CDS_ATTR(2(nodiscard, constexpr(14))) auto get(Union<Ts...>& u)
    CDS_ATTR(noexcept(false)) -> typename UnionBestMatch<T, Ts...>::Type& {
  return u.template get<T>();
}
} // namespace impl
} // namespace cds

CDS_ATTR(enable_warning(gcc, "-Wterminate"))

#endif // #ifndef CDS_PRIMITIVE_UNION_HPP
