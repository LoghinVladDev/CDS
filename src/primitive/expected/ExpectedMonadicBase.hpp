//
// Created by loghin on 7/29/25.
//

#ifndef CDS_PRIMITIVE_EXPECTED_MONADIC_BASE_HPP
#define CDS_PRIMITIVE_EXPECTED_MONADIC_BASE_HPP
#pragma once

#include <cds/functional/Invoke>
#include <cds/meta/Semantics>

#include "ExpectedDecl.hpp"
#include "ExpectedObservableBase.hpp"

namespace cds {
namespace impl {
using meta::InvokeReturnOf;
using meta::IsNoexceptInvocable;
using meta::IsVoid;
using meta::Not;
using meta::RemoveRef;

namespace fn = functional;

template <typename T, typename E> class ExpectedMonadicBase : public ExpectedObservableBase<T, E> {
  using Base = ExpectedObservableBase<T, E>;

protected:
  using Base::data;
  using Base::state;

public:
  using Base::Base;

  ExpectedMonadicBase() = default;
  ExpectedMonadicBase(ExpectedMonadicBase const&) = default;
  ExpectedMonadicBase(ExpectedMonadicBase&&) = default;
  auto operator=(ExpectedMonadicBase const&) -> ExpectedMonadicBase& = default;
  auto operator=(ExpectedMonadicBase&&) -> ExpectedMonadicBase& = default;
  ~ExpectedMonadicBase() = default;

  template <typename F, typename E0 = InvokeReturnOf<F, T&>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto then(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T&>)) -> E0 {
    return ExpectedState::Value == state()
           ? fn::invoke(fwd<F>(fn), data().value)
           : E0{Unexpect{}, data().error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T const&>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto then(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&>)) -> E0 {
    return ExpectedState::Value == state()
           ? fn::invoke(fwd<F>(fn), data().value)
           : E0{Unexpect{}, data().error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T&&>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto then(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T&&>)) -> E0 {
    return ExpectedState::Value == state()
           ? fn::invoke(fwd<F>(fn), mv(data()).value)
           : E0{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T const&&>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto then(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&&>)) -> E0 {
    return ExpectedState::Value == state()
           ? fn::invoke(fwd<F>(fn), mv(data()).value)
           : E0{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T&>>, EnableIf<Not<IsVoid<U>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T&>))
      -> Expected<U, E> {
    return ExpectedState::Value == state()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn), data().value)}
           : Expected<U, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T const&>>, EnableIf<Not<IsVoid<U>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto transform(F&& fn) const&
      CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&>)) -> Expected<U, E> {
    return ExpectedState::Value == state()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn), data().value)}
           : Expected<U, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T&&>>, EnableIf<Not<IsVoid<U>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T&&>))
      -> Expected<U, E> {
    return ExpectedState::Value == state()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn), mv(data()).value)}
           : Expected<U, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T const&&>>, EnableIf<Not<IsVoid<U>>>>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto transform(F&& fn) const&&
      CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&&>)) -> Expected<U, E> {
    return ExpectedState::Value == state()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn), mv(data()).value)}
           : Expected<U, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T&>>, EnableIf<IsVoid<U>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T&>))
      -> Expected<void, E> {
    if (ExpectedState::Value == state()) {
      fn::invoke(fwd<F>(fn), data().value);
    }

    return ExpectedState::Value == state()
           ? Expected<void, E>{}
           : Expected<void, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T const&>>, EnableIf<IsVoid<U>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn) const&
      CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&>)) -> Expected<void, E> {
    if (ExpectedState::Value == state()) {
      fn::invoke(fwd<F>(fn), data().value);
    }

    return ExpectedState::Value == state()
           ? Expected<void, E>{}
           : Expected<void, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T&&>>, EnableIf<IsVoid<U>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T&&>))
      -> Expected<void, E> {
    if (ExpectedState::Value == state()) {
      fn::invoke(fwd<F>(fn), mv(data()).value);
    }

    return ExpectedState::Value == state()
           ? Expected<void, E>{}
           : Expected<void, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T const&&>>, EnableIf<IsVoid<U>>>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn) const&&
      CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&&>)) -> Expected<void, E> {
    if (ExpectedState::Value == state()) {
      fn::invoke(fwd<F>(fn), mv(data()).value);
    }

    return ExpectedState::Value == state()
           ? Expected<void, E>{}
           : Expected<void, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto orElse(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&>)) -> Expected<T, E> {
    return ExpectedState::Value == state()
           ? static_cast<Expected<T, E>&>(*this)
           : fn::invoke(fwd<F>(fn), data().error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto orElse(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&>)) -> Expected<T, E> {
    return ExpectedState::Value == state()
           ? static_cast<Expected<T, E> const&>(*this)
           : fn::invoke(fwd<F>(fn), data().error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto orElse(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&&>)) -> Expected<T, E> {
    return ExpectedState::Value == state()
           ? static_cast<Expected<T, E>&&>(mv(*this))
           : fn::invoke(fwd<F>(fn), mv(data()).error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto orElse(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&&>)) -> Expected<T, E> {
    return ExpectedState::Value == state()
           ? static_cast<Expected<T, E> const&&>(mv(*this))
           : fn::invoke(fwd<F>(fn), mv(data()).error);
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transformError(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&>)) -> Expected<T, G> {
    return ExpectedState::Value == state()
           ? Expected<T, G>{data().value}
           : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), data().error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transformError(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&>)) -> Expected<T, G> {
    return ExpectedState::Value == state()
           ? Expected<T, G>{data().value}
           : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), data().error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transformError(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&&>)) -> Expected<T, G> {
    return ExpectedState::Value == state()
           ? Expected<T, G>{mv(data()).value}
           : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), mv(data()).error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transformError(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&&>)) -> Expected<T, G> {
    return ExpectedState::Value == state()
           ? Expected<T, G>{mv(data()).value}
           : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), mv(data()).error)};
  }
};

template <typename E> class ExpectedMonadicBase<void, E> : public ExpectedObservableBase<void, E> {
  using Base = ExpectedObservableBase<void, E>;

protected:
  using Base::data;
  using Base::state;

public:
  using Base::Base;

  ExpectedMonadicBase() = default;
  ExpectedMonadicBase(ExpectedMonadicBase const&) = default;
  ExpectedMonadicBase(ExpectedMonadicBase&&) = default;
  auto operator=(ExpectedMonadicBase const&) -> ExpectedMonadicBase& = default;
  auto operator=(ExpectedMonadicBase&&) -> ExpectedMonadicBase& = default;
  ~ExpectedMonadicBase() = default;

  template <typename F, typename E0 = InvokeReturnOf<F>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto then(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> E0 {
    return ExpectedState::Value == state()
           ? fn::invoke(fwd<F>(fn))
           : E0{Unexpect{}, data().error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto then(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> E0 {
    return ExpectedState::Value == state()
           ? fn::invoke(fwd<F>(fn))
           : E0{Unexpect{}, data().error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto then(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> E0 {
    return ExpectedState::Value == state()
           ? fn::invoke(fwd<F>(fn))
           : E0{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto then(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> E0 {
    return ExpectedState::Value == state()
           ? fn::invoke(fwd<F>(fn))
           : E0{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>, EnableIf<Not<IsVoid<U>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>))
      -> Expected<U, E> {
    return ExpectedState::Value == state()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
           : Expected<U, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>, EnableIf<Not<IsVoid<U>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto transform(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>))
      -> Expected<U, E> {
    return ExpectedState::Value == state()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
           : Expected<U, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>, EnableIf<Not<IsVoid<U>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>))
      -> Expected<U, E> {
    return ExpectedState::Value == state()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
           : Expected<U, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>, EnableIf<Not<IsVoid<U>>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto transform(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>))
      -> Expected<U, E> {
    return ExpectedState::Value == state()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
           : Expected<U, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>, EnableIf<IsVoid<U>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>))
      -> Expected<void, E> {
    if (ExpectedState::Value == state()) {
      fn::invoke(fwd<F>(fn));
    }

    return ExpectedState::Value == state()
           ? Expected<void, E>{}
           : Expected<void, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>, EnableIf<IsVoid<U>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>))
      -> Expected<void, E> {
    if (ExpectedState::Value == state()) {
      fn::invoke(fwd<F>(fn));
    }

    return ExpectedState::Value == state()
           ? Expected<void, E>{}
           : Expected<void, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>, EnableIf<IsVoid<U>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>))
      -> Expected<void, E> {
    if (ExpectedState::Value == state()) {
      fn::invoke(fwd<F>(fn));
    }

    return ExpectedState::Value == state()
           ? Expected<void, E>{}
           : Expected<void, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>, EnableIf<IsVoid<U>> = 0>
  CDS_ATTR(2(nodiscard, constexpr(14))) auto transform(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>))
      -> Expected<void, E> {
    if (ExpectedState::Value == state()) {
      fn::invoke(fwd<F>(fn));
    }

    return ExpectedState::Value == state()
           ? Expected<void, E>{}
           : Expected<void, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto orElse(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&>)) -> Expected<void, E> {
    return ExpectedState::Value == state()
           ? static_cast<Expected<void, E>&>(*this)
           : fn::invoke(fwd<F>(fn), data().error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto orElse(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&>)) -> Expected<void, E> {
    return ExpectedState::Value == state()
           ? static_cast<Expected<void, E> const&>(*this)
           : fn::invoke(fwd<F>(fn), data().error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto orElse(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&&>)) -> Expected<void, E> {
    return ExpectedState::Value == state()
           ? static_cast<Expected<void, E> &&>(mv(*this))
           : fn::invoke(fwd<F>(fn), mv(data()).error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto orElse(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&&>)) -> Expected<void, E> {
    return ExpectedState::Value == state()
           ? static_cast<Expected<void, E> const&&>(mv(*this))
           : fn::invoke(fwd<F>(fn), mv(data()).error);
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transformError(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&>)) -> Expected<void, G> {
    return ExpectedState::Value == state()
           ? Expected<void, G>{}
           : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), data().error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transformError(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&>)) -> Expected<void, G> {
    return ExpectedState::Value == state()
           ? Expected<void, G>{}
           : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), data().error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transformError(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&&>)) -> Expected<void, G> {
    return ExpectedState::Value == state()
           ? Expected<void, G>{}
           : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), mv(data()).error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transformError(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&&>)) -> Expected<void, G> {
    return ExpectedState::Value == state()
           ? Expected<void, G>{}
           : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), mv(data()).error)};
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_MONADIC_BASE_HPP
