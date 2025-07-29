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
using meta::RemoveRef;

namespace fn = functional;

template <typename T, typename E> class ExpectedMonadicBase : public ExpectedObservableBase<T, E> {
  using Base = ExpectedObservableBase<T, E>;

protected:
  using Base::data;
  using Base::engaged;

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
    return engaged()
           ? fn::invoke(fwd<F>(fn), data().value)
           : E0{Unexpect{}, data().error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T const&>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto then(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&>)) -> E0 {
    return engaged()
           ? fn::invoke(fwd<F>(fn), data().value)
           : E0{Unexpect{}, data().error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T&&>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto then(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T&&>)) -> E0 {
    return engaged()
           ? fn::invoke(fwd<F>(fn), mv(data()).value)
           : E0{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F, T const&&>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto then(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&&>)) -> E0 {
    return engaged()
           ? fn::invoke(fwd<F>(fn), mv(data()).value)
           : E0{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T&>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transform(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T&>)) -> Expected<U, E> {
    return engaged()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn), data().value)}
           : Expected<U, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T const&>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transform(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&>)) -> Expected<U, E> {
    return engaged()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn), data().value)}
           : Expected<U, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T&&>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transform(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T&&>)) -> Expected<U, E> {
    return engaged()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn), mv(data()).value)}
           : Expected<U, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F, T const&&>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transform(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, T const&&>)) -> Expected<U, E> {
    return engaged()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn), mv(data()).value)}
           : Expected<U, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto orElse(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&>)) -> Expected<T, E> {
    return engaged() ? *this : fn::invoke(fwd<F>(fn), data().error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto orElse(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&>)) -> Expected<T, E> {
    return engaged() ? *this : fn::invoke(fwd<F>(fn), data().error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto orElse(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&&>)) -> Expected<T, E> {
    return engaged() ? mv(*this) : fn::invoke(fwd<F>(fn), mv(data()).error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto orElse(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&&>)) -> Expected<T, E> {
    return engaged() ? mv(*this) : fn::invoke(fwd<F>(fn), mv(data()).error);
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transformError(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&>)) -> Expected<T, G> {
    return engaged()
           ? Expected<T, G>{data().value}
           : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), data().error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transformError(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&>)) -> Expected<T, G> {
    return engaged()
           ? Expected<T, G>{data().value}
           : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), data().error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transformError(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&&>)) -> Expected<T, G> {
    return engaged()
           ? Expected<T, G>{mv(data()).value}
           : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), mv(data()).error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transformError(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&&>)) -> Expected<T, G> {
    return engaged()
           ? Expected<T, G>{mv(data()).value}
           : Expected<T, G>{Unexpect{}, fn::invoke(fwd<F>(fn), mv(data()).error)};
  }
};

template <typename E> class ExpectedMonadicBase<void, E> : public ExpectedObservableBase<void, E> {
  using Base = ExpectedObservableBase<void, E>;

protected:
  using Base::data;
  using Base::engaged;

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
    return engaged()
           ? fn::invoke(fwd<F>(fn))
           : E0{Unexpect{}, data().error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto then(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> E0 {
    return engaged()
           ? fn::invoke(fwd<F>(fn))
           : E0{Unexpect{}, data().error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto then(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> E0 {
    return engaged()
           ? fn::invoke(fwd<F>(fn))
           : E0{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename E0 = InvokeReturnOf<F>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto then(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> E0 {
    return engaged()
           ? fn::invoke(fwd<F>(fn))
           : E0{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transform(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> Expected<U, E> {
    return engaged()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
           : Expected<U, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transform(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> Expected<U, E> {
    return engaged()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
           : Expected<U, E>{Unexpect{}, data().error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transform(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> Expected<U, E> {
    return engaged()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
           : Expected<U, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F, typename U = RemoveRef<InvokeReturnOf<F>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transform(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F>)) -> Expected<U, E> {
    return engaged()
           ? Expected<U, E>{fn::invoke(fwd<F>(fn))}
           : Expected<U, E>{Unexpect{}, mv(data()).error};
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto orElse(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&>)) -> Expected<void, E> {
    return engaged() ? *this : fn::invoke(fwd<F>(fn), data().error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto orElse(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&>)) -> Expected<void, E> {
    return engaged() ? *this : fn::invoke(fwd<F>(fn), data().error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto orElse(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&&>)) -> Expected<void, E> {
    return engaged() ? mv(*this) : fn::invoke(fwd<F>(fn), mv(data()).error);
  }

  template <typename F> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto orElse(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&&>)) -> Expected<void, E> {
    return engaged() ? mv(*this) : fn::invoke(fwd<F>(fn), mv(data()).error);
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transformError(F&& fn)& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&>)) -> Expected<void, G> {
    return engaged()
           ? Expected<void, G>{}
           : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), data().error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transformError(F&& fn) const& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&>)) -> Expected<void, G> {
    return engaged()
           ? Expected<void, G>{}
           : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), data().error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transformError(F&& fn)&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E&&>)) -> Expected<void, G> {
    return engaged()
           ? Expected<void, G>{}
           : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), mv(data()).error)};
  }

  template <typename F, typename G = RemoveRef<InvokeReturnOf<F, E>>> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transformError(F&& fn) const&& CDS_ATTR(noexcept_v(IsNoexceptInvocable<F, E const&&>)) -> Expected<void, G> {
    return engaged()
           ? Expected<void, G>{}
           : Expected<void, G>{Unexpect{}, fn::invoke(fwd<F>(fn), mv(data()).error)};
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_PRIMITIVE_EXPECTED_MONADIC_BASE_HPP
