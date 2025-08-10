//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_OBSERVABLE_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_OBSERVABLE_BASE_HPP
#pragma once

#include <cds/meta/ObjectTraits>
#include <cds/meta/Semantics>

#include "ExpectedMoveAssignableBase.hpp"
#include "ExpectedValueException.hpp"

namespace cds {
namespace impl {
using meta::And;
using meta::IsNoexceptConstructible;
using meta::IsNoexceptCopyConstructible;
using meta::IsNoexceptMoveConstructible;
using meta::RemoveConstVolatile;

template <typename T, typename E> class ExpectedObservableBase : public ExpectedMoveAssignableBase<T, E> {
  using Base = ExpectedMoveAssignableBase<T, E>;

protected:
  using Base::data;
  using Base::state;

public:
  using Base::Base;
  using Base::operator=;

  ExpectedObservableBase() = default;
  ExpectedObservableBase(ExpectedObservableBase const&) = default;
  ExpectedObservableBase(ExpectedObservableBase&&) = default;
  auto operator=(ExpectedObservableBase const&) -> ExpectedObservableBase& = default;
  auto operator=(ExpectedObservableBase&&) -> ExpectedObservableBase& = default;
  ~ExpectedObservableBase() = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto hasValue() const noexcept -> bool {
    return ExpectedState::Value == state();
  }

  CDS_ATTR(3(nodiscard, explicit, constexpr(11))) operator bool() const noexcept {
    return ExpectedState::Value == state();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator->() const noexcept -> T const* {
#if CDS_ATTR(cpp14)
    assert(ExpectedState::Value == state() && "undefined behavior");
#endif
    return &data().value;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator->() noexcept -> T* {
    assert(ExpectedState::Value == state() && "undefined behavior");
    return &data().value;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const& noexcept -> T const& {
#if CDS_ATTR(cpp14)
    assert(ExpectedState::Value == state() && "undefined behavior");
#endif
    return data().value;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const&& noexcept -> T const&& {
#if CDS_ATTR(cpp14)
    assert(ExpectedState::Value == state() && "undefined behavior");
#endif
    return mv(data()).value;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator*()& noexcept -> T& {
    assert(ExpectedState::Value == state() && "undefined behavior");
    return data().value;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator*()&& noexcept -> T&& {
    assert(ExpectedState::Value == state() && "undefined behavior");
    return mv(data()).value;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto value() const& CDS_ATTR(noexcept(false)) -> T const& {
    if (ExpectedState::Value != state()) {
      throw ExpectedValueException<E>(data().error);
    }
    return data().value;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto value() const&& CDS_ATTR(noexcept(false)) -> T const&& {
    if (ExpectedState::Value != state()) {
      throw ExpectedValueException<E>(mv(data()).error);
    }
    return mv(data()).value;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto value()& CDS_ATTR(noexcept(false)) -> T& {
    if (ExpectedState::Value != state()) {
      throw ExpectedValueException<E>(data().error);
    }
    return data().value;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto value()&& CDS_ATTR(noexcept(false)) -> T&& {
    if (ExpectedState::Value != state()) {
      throw ExpectedValueException<E>(mv(data()).error);
    }
    return mv(data()).value;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto error() const& noexcept -> E const& {
#if CDS_ATTR(cpp14)
    assert(ExpectedState::Error == state() && "undefined behavior");
#endif
    return data().error;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto error() const&& noexcept -> E const&& {
#if CDS_ATTR(cpp14)
    assert(ExpectedState::Error == state() && "undefined behavior");
#endif
    return mv(data()).error;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto error()& noexcept -> E& {
    assert(ExpectedState::Error == state() && "undefined behavior");
    return data().error;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto error()&& noexcept -> E&& {
    assert(ExpectedState::Error == state() && "undefined behavior");
    return mv(data()).error;
  }

  template <typename U = RemoveConstVolatile<T>> CDS_ATTR(2(nodiscard, constexpr(11))) auto valueOr(U&& defaultValue)
      const& CDS_ATTR(noexcept_v(And<IsNoexceptCopyConstructible<T>, IsNoexceptConstructible<T, U&&>>)) -> T {
    return ExpectedState::Value == state() ? data().value : static_cast<T>(fwd<U>(defaultValue));
  }

  template <typename U = RemoveConstVolatile<T>> CDS_ATTR(2(nodiscard, constexpr(14))) auto valueOr(U&& defaultValue)
      && CDS_ATTR(noexcept_v(And<IsNoexceptMoveConstructible<T>, IsNoexceptConstructible<T, U&&>>)) -> T {
    return ExpectedState::Value == state() ? mv(data()).value : static_cast<T>(fwd<U>(defaultValue));
  }

  template <typename G = RemoveConstVolatile<E>> CDS_ATTR(2(nodiscard, constexpr(11))) auto errorOr(G&& defaultValue)
      const& CDS_ATTR(noexcept_v(And<IsNoexceptCopyConstructible<E>, IsNoexceptConstructible<E, G&&>>)) -> E {
    return ExpectedState::Error == state() ? data().error : static_cast<E>(fwd<G>(defaultValue));
  }

  template <typename G = RemoveConstVolatile<E>> CDS_ATTR(2(nodiscard, constexpr(14))) auto errorOr(G&& defaultValue)
      && CDS_ATTR(noexcept_v(And<IsNoexceptMoveConstructible<E>, IsNoexceptConstructible<E, G&&>>)) -> E {
    return ExpectedState::Error == state() ? mv(data()).error : static_cast<E>(fwd<G>(defaultValue));
  }
};

template <typename E> class ExpectedObservableBase<void, E> : public ExpectedMoveAssignableBase<void, E> {
  using Base = ExpectedMoveAssignableBase<void, E>;

protected:
  using Base::data;
  using Base::state;

public:
  using Base::Base;
  using Base::operator=;

  ExpectedObservableBase() = default;
  ExpectedObservableBase(ExpectedObservableBase const&) = default;
  ExpectedObservableBase(ExpectedObservableBase&&) = default;
  auto operator=(ExpectedObservableBase const&) -> ExpectedObservableBase& = default;
  auto operator=(ExpectedObservableBase&&) -> ExpectedObservableBase& = default;
  ~ExpectedObservableBase() = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto hasValue() const noexcept -> bool {
    return ExpectedState::Value == state();
  }

  CDS_ATTR(3(nodiscard, explicit, constexpr(11))) operator bool() const noexcept {
    return ExpectedState::Value == state();
  }

  CDS_ATTR(constexpr(14)) auto operator*() const noexcept -> void {
    assert(ExpectedState::Value == state() && "undefined behavior");
    /* nothing */
  }

  CDS_ATTR(constexpr(14)) auto value() const& -> void {
    if (ExpectedState::Value != state()) {
      throw ExpectedValueException<E>(data().error);
    }
  }

  CDS_ATTR(constexpr(14)) auto value()&& -> void {
    if (ExpectedState::Value != state()) {
      throw ExpectedValueException<E>(data().error);
    }
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto error() const& noexcept -> E const& {
#if CDS_ATTR(cpp14)
    assert(ExpectedState::Error == state() && "undefined behavior");
#endif
    return data().error;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto error() const&& noexcept -> E const&& {
#if CDS_ATTR(cpp14)
    assert(ExpectedState::Error == state() && "undefined behavior");
#endif
    return mv(data()).error;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto error()& noexcept -> E& {
    assert(ExpectedState::Error == state() && "undefined behavior");
    return data().error;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto error()&& noexcept -> E&& {
    assert(ExpectedState::Error == state() && "undefined behavior");
    return mv(data()).error;
  }

  template <typename G = RemoveConstVolatile<E>> CDS_ATTR(2(nodiscard, constexpr(11))) auto errorOr(G&& defaultValue)
      const& CDS_ATTR(noexcept_v(And<IsNoexceptCopyConstructible<E>, IsNoexceptConstructible<E, G&&>>)) -> E {
    return ExpectedState::Error == state() ? data().error : static_cast<E>(fwd<G>(defaultValue));
  }

  template <typename G = RemoveConstVolatile<E>> CDS_ATTR(2(nodiscard, constexpr(14))) auto errorOr(G&& defaultValue)
      && CDS_ATTR(noexcept_v(And<IsNoexceptMoveConstructible<E>, IsNoexceptConstructible<E, G&&>>)) -> E {
    return ExpectedState::Error == state() ? mv(data()).error : static_cast<E>(fwd<G>(defaultValue));
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_OBSERVABLE_BASE_HPP
