//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_DESTRUCTIBLE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_DESTRUCTIBLE_BASE_HPP
#pragma once

#include <initializer_list>

#include <cds/meta/ObjectTraits>
#include <cds/meta/Tags>
#include <cds/memory/ByteStorage>

#include "ExpectedSpecialMemberFunctionsDetail.hpp"
#include "ExpectedStorageBase.hpp"

namespace cds {
namespace impl {
using meta::address;
using meta::IsConstructible;
using meta::IsNoexceptConstructible;
using meta::SpecialMemberFunctionInfoType;

enum class ExpectedState : U8 {
  Uninitialized, Value, Error
};

template <typename T, typename E, SpecialMemberFunctionInfoType = ExpectedDestructionDetail<T, E>::value>
class ExpectedDestructibleBase;

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
      _state{ExpectedState::Value},
      _data{InPlace{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args, EnableIf<IsConstructible<T, std::initializer_list<U> const&, Args&&...>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) :
      _state{ExpectedState::Value},
      _data{InPlace{}, list, fwd<Args>(args)...} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _state{ExpectedState::Error},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _state{ExpectedState::Error},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Uninitialized) noexcept :
      _data{Uninitialized{}},
      _state{ExpectedState::Uninitialized} {}

  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    _state = ExpectedState::Uninitialized;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto state() const noexcept -> ExpectedState {
    return _state;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto state() noexcept -> ExpectedState& {
    return _state;
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

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data&& {
    return mv(_data);
  }

private:
  ExpectedState _state;
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
      _state{ExpectedState::Value},
      _data{InPlace{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args, EnableIf<IsConstructible<T, std::initializer_list<U> const&, Args&&...>> = 0>
  CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<T, std::initializer_list<U> const&, Args&&...>)) :
      _state{ExpectedState::Value},
      _data{InPlace{}, list, fwd<Args>(args)...} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _state{ExpectedState::Error},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _state{ExpectedState::Error},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Uninitialized) noexcept :
      _data{Uninitialized{}},
      _state{ExpectedState::Uninitialized} {}

  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    switch (_state) {
      case ExpectedState::Value:
        destruct(&_data.value);
        break;
      case ExpectedState::Error:
        destruct(&_data.error);
        break;
      case ExpectedState::Uninitialized:
        return;
    }

    _state = ExpectedState::Uninitialized;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto state() const noexcept -> ExpectedState {
    return _state;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto state() noexcept -> ExpectedState& {
    return _state;
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

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data&& {
    return mv(_data);
  }

private:
  ExpectedState _state;
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
      typename... Args, EnableIf<And<
          DoesNotHide<ExpectedDestructibleBase, Args&&...>,
          IsConstructible<ByteStorage<Data>, InPlace, Args&&...>
      >> = 0
  > CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<ByteStorage<Data>, InPlace, Args&&...>)) :
      _state{ExpectedState::Value},
      _storage{InPlace{}, fwd<Args>(args)...} {}

  template <
      typename U, typename... Args,
      EnableIf<IsConstructible<ByteStorage<Data>, InPlace, std::initializer_list<U> const&, Args&&...>> = 0
  > CDS_ATTR(2(implicit, constexpr(11))) ExpectedDestructibleBase(std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(
          IsNoexceptConstructible<ByteStorage<Data>, InPlace, std::initializer_list<U> const&, Args&&...>
      )) :
      _state{ExpectedState::Value},
      _storage{InPlace{}, list, fwd<Args>(args)...} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<ByteStorage<Data>, Unexpect, Args&&...>)) :
      _state{ExpectedState::Error},
      _storage{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args) CDS_ATTR(noexcept_v(
      IsNoexceptConstructible<ByteStorage<Data>, Unexpect, std::initializer_list<U> const&, Args&&...>
  )) :
      _state{ExpectedState::Error},
      _storage{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Uninitialized) noexcept :
      _state{ExpectedState::Uninitialized},
      _storage{Uninitialized{}} {}

  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    /* nothing */
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto state() const noexcept -> ExpectedState {
    return _state;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto state() noexcept -> ExpectedState& {
    return _state;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const& noexcept -> Data const& {
    return _storage.obj();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const&& noexcept -> Data const&& {
    return mv(_storage.obj());
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()& noexcept -> Data& {
    return _storage.obj();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data&& {
    return mv(_storage.obj());
  }

private:
  ExpectedState _state;
  ByteStorage<Data> _storage;
};

template <typename E> class ExpectedDestructibleBase<void, E, SpecialMemberFunctionInfoType::Trivial> {
  using Data = ExpectedStorageBase<void, E>;

public:
  ExpectedDestructibleBase(ExpectedDestructibleBase const&) = default;
  ExpectedDestructibleBase(ExpectedDestructibleBase&&) = default;
  auto operator=(ExpectedDestructibleBase const&) -> ExpectedDestructibleBase& = default;
  auto operator=(ExpectedDestructibleBase&&) -> ExpectedDestructibleBase& = default;
  ~ExpectedDestructibleBase() = default;

  CDS_ATTR(constexpr(11)) ExpectedDestructibleBase() noexcept : _state{ExpectedState::Value}, _data{InPlace{}} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _state{ExpectedState::Error},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _state{ExpectedState::Error},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Uninitialized) noexcept :
      _data{Uninitialized{}},
      _state{ExpectedState::Uninitialized} {}

  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    _state = ExpectedState::Uninitialized;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto state() const noexcept -> ExpectedState {
    return _state;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto state() noexcept -> ExpectedState& {
    return _state;
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

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data&& {
    return mv(_data);
  }

private:
  ExpectedState _state;
  Data _data;
};

template <typename E> class ExpectedDestructibleBase<void, E, SpecialMemberFunctionInfoType::NonTrivial> {
  using Data = ExpectedStorageBase<void, E>;

public:
  ExpectedDestructibleBase(ExpectedDestructibleBase const&) = default;
  ExpectedDestructibleBase(ExpectedDestructibleBase&&) = default;
  auto operator=(ExpectedDestructibleBase const&) -> ExpectedDestructibleBase& = default;
  auto operator=(ExpectedDestructibleBase&&) -> ExpectedDestructibleBase& = default;

  CDS_ATTR(constexpr(11)) ExpectedDestructibleBase() noexcept : _state{ExpectedState::Value}, _data{InPlace{}} {}

  CDS_ATTR(constexpr(20)) ~ExpectedDestructibleBase() {
    destroy();
  }

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _state{ExpectedState::Error},
      _data{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _state{ExpectedState::Error},
      _data{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Uninitialized) noexcept :
      _data{Uninitialized{}},
      _state{ExpectedState::Uninitialized} {}

  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    if (ExpectedState::Error == xch(_state, ExpectedState::Uninitialized)) {
      destruct(&_data.error);
    }
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto state() const noexcept -> ExpectedState {
    return _state;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto state() noexcept -> ExpectedState& {
    return _state;
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

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data&& {
    return mv(_data);
  }

private:
  ExpectedState _state;
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

  CDS_ATTR(constexpr(11)) ExpectedDestructibleBase() noexcept : _state{ExpectedState::Value}, _storage{InPlace{}} {}

  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Unexpect, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, Args&&...>)) :
      _state{ExpectedState::Error},
      _storage{Unexpect{}, fwd<Args>(args)...} {}

  template <typename U, typename... Args> CDS_ATTR(constexpr(11))
  ExpectedDestructibleBase(Unexpect, std::initializer_list<U> const& list, Args&&... args)
      CDS_ATTR(noexcept_v(IsNoexceptConstructible<E, std::initializer_list<U> const&, Args&&...>)) :
      _state{ExpectedState::Error},
      _storage{Unexpect{}, list, fwd<Args>(args)...} {}

protected:
  CDS_ATTR(2(explicit, constexpr(11))) ExpectedDestructibleBase(Uninitialized) noexcept :
      _state{ExpectedState::Uninitialized},
      _storage{Uninitialized{}} {}

  CDS_ATTR(constexpr(14)) auto destroy() noexcept -> void {
    /* nothing */
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto state() const noexcept -> ExpectedState {
    return _state;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto state() noexcept -> ExpectedState& {
    return _state;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const& noexcept -> Data const& {
    return _storage.obj();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto data() const&& noexcept -> Data const&& {
    return mv(_storage.obj());
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()& noexcept -> Data& {
    return _storage.obj();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto data()&& noexcept -> Data&& {
    return mv(_storage.obj());
  }

private:
  ExpectedState _state;
  ByteStorage<Data> _storage;
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_DESTRUCTIBLE_BASE_HPP
