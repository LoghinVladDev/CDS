//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_DESTRUCTIBLE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_DESTRUCTIBLE_BASE_HPP
#pragma once

#include <initializer_list>

#include <cds/meta/ObjectTraits>
#include <cds/meta/Tags>

#include "ExpectedSpecialMemberFunctionsDetail.hpp"
#include "ExpectedStorageBase.hpp"

namespace cds {
namespace impl {
using meta::IsConstructible;
using meta::IsNoexceptConstructible;
using meta::SpecialMemberFunctionInfoType;

template <typename T, typename E, SpecialMemberFunctionInfoType = ExpectedDestructionDetail<T, E>::value>
struct ExpectedDestructibleBase;

template <typename T, typename E> class ExpectedDestructibleBase<T, E, SpecialMemberFunctionInfoType::Trivial> {
  using Data = ExpectedStorageBase<T, E>;

public:
  ExpectedDestructibleBase(ExpectedDestructibleBase const&) = default;
  ExpectedDestructibleBase(ExpectedDestructibleBase&&) = default;
  auto operator=(ExpectedDestructibleBase const&) -> ExpectedDestructibleBase& = default;
  auto operator=(ExpectedDestructibleBase&&) -> ExpectedDestructibleBase& = default;
  ~ExpectedDestructibleBase() = default;

  template <
      typename... Args,
      EnableIf<And<DoesNotHide<ExpectedDestructibleBase, Args&&...>, IsConstructible<T, Args&&...>>> = 0
  > CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, Args&&...>)) :
      _engaged{true},
      _data{InPlace{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args, EnableIf<IsConstructible<T, Args&&...>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) :
      _engaged{true},
      _data{InPlace{}, list, fwd<Args>(args)...} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    _engaged = false;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto engaged() const noexcept -> bool {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto engaged() noexcept -> bool& {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const& noexcept -> Data const& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const&& noexcept -> Data const&& {
    return mv(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()& noexcept -> Data& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data& {
    return mv(_data);
  }

private:
  bool _engaged;
  Data _data;
};

template <typename T, typename E> class ExpectedDestructibleBase<T, E, SpecialMemberFunctionInfoType::NonTrivial> {
  using Data = ExpectedStorageBase<T, E>;

public:
  ExpectedDestructibleBase(ExpectedDestructibleBase const&) = default;
  ExpectedDestructibleBase(ExpectedDestructibleBase&&) = default;
  auto operator=(ExpectedDestructibleBase const&) -> ExpectedDestructibleBase& = default;
  auto operator=(ExpectedDestructibleBase&&) -> ExpectedDestructibleBase& = default;

  CDS_ATTR(constexpr(20)) ~ExpectedDestructibleBase() {
    destroy();
  }

  template <
      typename... Args,
      EnableIf<And<DoesNotHide<ExpectedDestructibleBase, Args&&...>, IsConstructible<T, Args&&...>>> = 0
  > CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, Args&&...>)) :
      _engaged{true},
      _data{InPlace{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args, EnableIf<IsConstructible<T, Args&&...>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) :
      _engaged{true},
      _data{InPlace{}, list, fwd<Args>(args)...} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    if (_engaged) {
      destruct(&_data.value);
    } else {
      destruct(&_data.error);
    }
    _engaged = false;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto engaged() const noexcept -> bool {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto engaged() noexcept -> bool& {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const& noexcept -> Data const& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const&& noexcept -> Data const&& {
    return mv(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()& noexcept -> Data& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data& {
    return mv(_data);
  }

private:
  bool _engaged;
  Data _data;
};

template <typename T, typename E> class ExpectedDestructibleBase<T, E, SpecialMemberFunctionInfoType::Deleted> {
  using Data = ExpectedStorageBase<T, E>;

public:
  ExpectedDestructibleBase(ExpectedDestructibleBase const&) = default;
  ExpectedDestructibleBase(ExpectedDestructibleBase&&) = default;
  auto operator=(ExpectedDestructibleBase const&) -> ExpectedDestructibleBase& = default;
  auto operator=(ExpectedDestructibleBase&&) -> ExpectedDestructibleBase& = default;
  ~ExpectedDestructibleBase() = delete;

  template <
      typename... Args,
      EnableIf<And<DoesNotHide<ExpectedDestructibleBase, Args&&...>, IsConstructible<T, Args&&...>>> = 0
  > CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, Args&&...>)) :
      _engaged{true},
      _data{InPlace{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args, EnableIf<IsConstructible<T, Args&&...>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) :
      _engaged{true},
      _data{InPlace{}, list, fwd<Args>(args)...} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    /* nothing */
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto engaged() const noexcept -> bool {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto engaged() noexcept -> bool& {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const& noexcept -> Data const& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const&& noexcept -> Data const&& {
    return mv(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()& noexcept -> Data& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data& {
    return mv(_data);
  }

private:
  bool _engaged;
  Data _data;
};

template <typename E> class ExpectedDestructibleBase<void, E, SpecialMemberFunctionInfoType::Trivial> {
  using Data = ExpectedStorageBase<void, E>;

public:
  ExpectedDestructibleBase(ExpectedDestructibleBase const&) = default;
  ExpectedDestructibleBase(ExpectedDestructibleBase&&) = default;
  auto operator=(ExpectedDestructibleBase const&) -> ExpectedDestructibleBase& = default;
  auto operator=(ExpectedDestructibleBase&&) -> ExpectedDestructibleBase& = default;
  ~ExpectedDestructibleBase() = default;

  CDS_ATTR(constexpr(11)) ExpectedDestructibleBase() noexcept : _engaged{true}, _data{InPlace{}} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    _engaged = false;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto engaged() const noexcept -> bool {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto engaged() noexcept -> bool& {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const& noexcept -> Data const& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const&& noexcept -> Data const&& {
    return mv(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()& noexcept -> Data& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data& {
    return mv(_data);
  }

private:
  bool _engaged;
  Data _data;
};

template <typename E> class ExpectedDestructibleBase<void, E, SpecialMemberFunctionInfoType::NonTrivial> {
  using Data = ExpectedStorageBase<void, E>;

public:
  ExpectedDestructibleBase(ExpectedDestructibleBase const&) = default;
  ExpectedDestructibleBase(ExpectedDestructibleBase&&) = default;
  auto operator=(ExpectedDestructibleBase const&) -> ExpectedDestructibleBase& = default;
  auto operator=(ExpectedDestructibleBase&&) -> ExpectedDestructibleBase& = default;

  CDS_ATTR(constexpr(11)) ExpectedDestructibleBase() noexcept : _engaged{true}, _data{InPlace{}} {}

  CDS_ATTR(constexpr(20)) ~ExpectedDestructibleBase() {
    destroy();
  }

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    if (!xch(_engaged, false)) {
      destruct(&_data.error);
    }
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto engaged() const noexcept -> bool {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto engaged() noexcept -> bool& {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const& noexcept -> Data const& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const&& noexcept -> Data const&& {
    return mv(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()& noexcept -> Data& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data& {
    return mv(_data);
  }

private:
  bool _engaged;
  Data _data;
};

template <typename E> class ExpectedDestructibleBase<void, E, SpecialMemberFunctionInfoType::Deleted> {
  using Data = ExpectedStorageBase<void, E>;

public:
  ExpectedDestructibleBase(ExpectedDestructibleBase const&) = default;
  ExpectedDestructibleBase(ExpectedDestructibleBase&&) = default;
  auto operator=(ExpectedDestructibleBase const&) -> ExpectedDestructibleBase& = default;
  auto operator=(ExpectedDestructibleBase&&) -> ExpectedDestructibleBase& = default;
  ~ExpectedDestructibleBase() = delete;

  CDS_ATTR(constexpr(11)) ExpectedDestructibleBase() noexcept : _engaged{true}, _data{InPlace{}} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _engaged{false},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    /* nothing */
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto engaged() const noexcept -> bool {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto engaged() noexcept -> bool& {
    return _engaged;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const& noexcept -> Data const& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const&& noexcept -> Data const&& {
    return mv(_data);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()& noexcept -> Data& {
    return _data;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data& {
    return mv(_data);
  }

private:
  bool _engaged;
  Data _data;
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_DESTRUCTIBLE_BASE_HPP
