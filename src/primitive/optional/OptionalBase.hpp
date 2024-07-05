//
// Created by loghin on 6/21/24.
//

#ifndef CDS_PRIMITIVE_OPTIONAL_BASE_HPP
#define CDS_PRIMITIVE_OPTIONAL_BASE_HPP
#pragma once

#include <cds/exception/NoSuchElementException>

#include <cds/meta/ObjectTraits>
#include <cds/meta/StdLib>

namespace cds {
template <typename T> class Optional;

namespace impl {
struct Nullopt {};

constexpr Nullopt nullopt;

using meta::IsNoexceptConstructible;
using meta::IsNoexceptCopyConstructible;
using meta::IsNoexceptMoveConstructible;
using meta::IsNoexceptCopyAssignable;
using meta::IsNoexceptMoveAssignable;
using meta::IsNoexceptAssignable;
using meta::IsNoexceptDefaultConstructible;
using meta::IsTriviallyDestructible;
using meta::IsTriviallyCopyConstructible;
using meta::IsTriviallyMoveConstructible;
using meta::IsTriviallyCopyAssignable;
using meta::IsTriviallyMoveAssignable;
using meta::EnableIf;
using meta::InvokeReturnOf;
using meta::Not;
using meta::IsSame;
using meta::RemoveCVRef;
using meta::IsLValRef;
using meta::And;
using meta::True;
using meta::False;
using meta::IsInvocable;

using meta::lvalue;
using meta::rvalue;

namespace f = functional;

struct InPlace {};

template <typename T, typename = typename IsTriviallyDestructible<T>::Type> struct OptionalStorageBase {};

template <typename T> struct OptionalStorageBase<T, True> {
  CDS_ATTR(constexpr(11)) OptionalStorageBase() noexcept : _uninitialized{}, _exists{false} {}
  CDS_ATTR(constexpr(11)) OptionalStorageBase(CDS_ATTR(unused) InPlace)
      CDS_ATTR(noexcept(IsNoexceptDefaultConstructible<T>::value)) : _object{}, _exists{true} {}

  template <typename A, EnableIf<And<
      Not<IsSame<OptionalStorageBase, RemoveCVRef<A>>>,
      Not<IsSame<InPlace, RemoveCVRef<A>>>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) OptionalStorageBase(A&& arg)
      CDS_ATTR(noexcept(IsNoexceptConstructible<T, A>::value)) : _object(cds::forward<A>(arg)), _exists{true} {}

  template <typename A1, typename A2, typename... An> CDS_ATTR(constexpr(11))
  OptionalStorageBase(A1&& _1, A2&& _2, An&&... n)
      CDS_ATTR(noexcept(IsNoexceptConstructible<T, A1, A2, An...>::value)) :
      _object(cds::forward<A1>(_1), cds::forward<A2>(_2), cds::forward<An>(n)...), _exists{true} {}

  CDS_ATTR(constexpr(14)) auto reset() noexcept -> void {
    _exists = false;
  }

  ~OptionalStorageBase() noexcept = default;

  union {
    T _object;
    U8 _uninitialized;
  };
  bool _exists;
};

template <typename T> struct OptionalStorageBase<T, False> {
  CDS_ATTR(constexpr(11)) OptionalStorageBase() noexcept : _uninitialized{}, _exists{false} {}
  CDS_ATTR(constexpr(11)) OptionalStorageBase(CDS_ATTR(unused) InPlace)
      CDS_ATTR(noexcept(IsNoexceptDefaultConstructible<T>::value)) : _object{}, _exists{true} {}

  template <typename A, EnableIf<And<
      Not<IsSame<OptionalStorageBase, RemoveCVRef<A>>>,
      Not<IsSame<InPlace, RemoveCVRef<A>>>
  >> = 0> CDS_ATTR(2(implicit, constexpr(11))) OptionalStorageBase(A&& arg)
      CDS_ATTR(noexcept(IsNoexceptConstructible<T, A>::value)) : _object(cds::forward<A>(arg)), _exists{true} {}

  template <typename A1, typename A2, typename... An> CDS_ATTR(constexpr(11))
  OptionalStorageBase(A1&& _1, A2&& _2, An&&... n)
      CDS_ATTR(noexcept(IsNoexceptConstructible<T, A1, A2, An...>::value)) :
      _object(cds::forward<A1>(_1), cds::forward<A2>(_2), cds::forward<An>(n)...), _exists{true} {}

  CDS_ATTR(constexpr(20)) ~OptionalStorageBase() noexcept {
    if (_exists) {
      _object.~T();
    }
  }

  CDS_ATTR(constexpr(14)) auto reset() noexcept -> void {
    if (_exists) {
      _object.~T();
      _exists = false;
    }
  }

  union {
    T _object;
    U8 _uninitialized;
  };
  bool _exists;
};

template <typename, typename A, typename = typename IsLValRef<A>::Type>
struct OptionalLogicalBaseIsNoexceptConstructible {};

template <typename T, typename A> struct CDS_ATTR(inheritsEBOs) OptionalLogicalBaseIsNoexceptConstructible<T, A, True> :
    IsNoexceptCopyConstructible<T>::Type {};
template <typename T, typename A> struct CDS_ATTR(inheritsEBOs) OptionalLogicalBaseIsNoexceptConstructible<T, A, False>
    : IsNoexceptMoveConstructible<T>::Type {};

template <typename, typename A, typename = typename IsLValRef<A>::Type>
struct OptionalLogicalBaseIsNoexceptAssignable {};

template <typename T, typename A> struct CDS_ATTR(inheritsEBOs) OptionalLogicalBaseIsNoexceptAssignable<T, A, True> :
    And<IsNoexceptCopyConstructible<T>, IsNoexceptCopyAssignable<T>>::Type {};
template <typename T, typename A> struct CDS_ATTR(inheritsEBOs) OptionalLogicalBaseIsNoexceptAssignable<T, A, False> :
    And<IsNoexceptMoveConstructible<T>, IsNoexceptMoveAssignable<T>>::Type {};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalLogicalBase : OptionalStorageBase<T> {
  using LocalBase = OptionalStorageBase<T>;
  using LocalBase::_object;
  using LocalBase::_exists;
  using LocalBase::reset;
  using LocalBase::LocalBase;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto uncheckedGet() const& noexcept -> T const& {
    return _object;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto uncheckedGet()& noexcept -> T& {
    return _object;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto uncheckedGet() const&& noexcept -> T const&& {
    return cds::move(_object);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto uncheckedGet()&& noexcept -> T&& {
    return cds::move(_object);
  }

  template <typename A> CDS_ATTR(constexpr(20)) auto constructFrom(A&& arg)
      CDS_ATTR(noexcept(OptionalLogicalBaseIsNoexceptConstructible<T, A>::value)) -> void {
    if (arg._exists) {
			_exists = true;
      construct(&_object, cds::forward<A>(arg).uncheckedGet());
    }
  }

  template <typename A> CDS_ATTR(constexpr(20)) auto assignFrom(A&& arg)
      CDS_ATTR(noexcept(OptionalLogicalBaseIsNoexceptAssignable<T, A>::value)) -> void {
    if (_exists == arg._exists) {
      if (_exists) {
        _object = cds::forward<A>(arg).uncheckedGet();
      }
    } else if (_exists) {
      reset();
    } else {
      construct(&_object, cds::forward<A>(arg).uncheckedGet());
      _exists = true;
    }
  }
};

template <typename T, typename = typename IsTriviallyCopyConstructible<T>::Type> struct OptionalCopyConstructBase {};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalCopyConstructBase<T, True> : OptionalLogicalBase<T> {
  using LocalBase = OptionalLogicalBase<T>;
  using LocalBase::LocalBase;
};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalCopyConstructBase<T, False> : OptionalLogicalBase<T> {
  using LocalBase = OptionalLogicalBase<T>;
  using LocalBase::LocalBase;
  using LocalBase::constructFrom;

  OptionalCopyConstructBase() = default;

  CDS_ATTR(constexpr(20)) OptionalCopyConstructBase(OptionalCopyConstructBase const& object)
      CDS_ATTR(noexcept(noexcept(constructFrom(object)))) {
    constructFrom(object);
  }

  OptionalCopyConstructBase(OptionalCopyConstructBase&&) = default;
  auto operator=(OptionalCopyConstructBase const&) -> OptionalCopyConstructBase& = default;
  auto operator=(OptionalCopyConstructBase&&) -> OptionalCopyConstructBase& = default;
  ~OptionalCopyConstructBase() = default;
};

template <typename T, typename = typename IsTriviallyMoveConstructible<T>::Type> struct OptionalMoveConstructBase {};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalMoveConstructBase<T, True> : OptionalCopyConstructBase<T> {
  using LocalBase = OptionalCopyConstructBase<T>;
  using LocalBase::LocalBase;
};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalMoveConstructBase<T, False> : OptionalCopyConstructBase<T> {
  using LocalBase = OptionalCopyConstructBase<T>;
  using LocalBase::LocalBase;
  using LocalBase::constructFrom;

  OptionalMoveConstructBase() = default;
  OptionalMoveConstructBase(OptionalMoveConstructBase const&) = default;

  CDS_ATTR(constexpr(20)) OptionalMoveConstructBase(OptionalMoveConstructBase&& object)
      CDS_ATTR(noexcept(noexcept(constructFrom(cds::move(object))))) {
    constructFrom(cds::move(object));
  }

  auto operator=(OptionalMoveConstructBase const&) -> OptionalMoveConstructBase& = default;
  auto operator=(OptionalMoveConstructBase&&) -> OptionalMoveConstructBase& = default;
  ~OptionalMoveConstructBase() = default;
};

template <typename T, typename = typename IsTriviallyCopyAssignable<T>::Type> struct OptionalCopyAssignBase {};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalCopyAssignBase<T, True> : OptionalMoveConstructBase<T> {
  using LocalBase = OptionalMoveConstructBase<T>;
  using LocalBase::LocalBase;
};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalCopyAssignBase<T, False> : OptionalMoveConstructBase<T> {
  using LocalBase = OptionalMoveConstructBase<T>;
  using LocalBase::LocalBase;
  using LocalBase::assignFrom;

  OptionalCopyAssignBase() = default;
  OptionalCopyAssignBase(OptionalCopyAssignBase const&) = default;
  OptionalCopyAssignBase(OptionalCopyAssignBase&&) = default;

  CDS_ATTR(constexpr(20)) auto operator=(OptionalCopyAssignBase const& object)
      CDS_ATTR(noexcept(noexcept(assignFrom(object)))) -> OptionalCopyAssignBase& {
    assignFrom(object);
    return *this;
  }

  auto operator=(OptionalCopyAssignBase&&) -> OptionalCopyAssignBase& = default;
  ~OptionalCopyAssignBase() = default;
};

template <typename T, typename = typename IsTriviallyMoveAssignable<T>::Type> struct OptionalMoveAssignBase {};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalMoveAssignBase<T, True> : OptionalCopyAssignBase<T> {
  using LocalBase = OptionalCopyAssignBase<T>;
  using LocalBase::LocalBase;
};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalMoveAssignBase<T, False> : OptionalCopyAssignBase<T> {
  using LocalBase = OptionalCopyAssignBase<T>;
  using LocalBase::LocalBase;
  using LocalBase::assignFrom;

  OptionalMoveAssignBase() = default;
  OptionalMoveAssignBase(OptionalMoveAssignBase const&) = default;
  OptionalMoveAssignBase(OptionalMoveAssignBase&&) = default;
  auto operator=(OptionalMoveAssignBase const&) -> OptionalMoveAssignBase& = default;

  CDS_ATTR(constexpr(20)) auto operator=(OptionalMoveAssignBase&& object)
      CDS_ATTR(noexcept(noexcept(assignFrom(cds::move(object))))) -> OptionalMoveAssignBase& {
    assignFrom(cds::move(object));
    return *this;
  }

  ~OptionalMoveAssignBase() = default;
};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalObservableBase : OptionalMoveAssignBase<T> {
  using LocalBase = OptionalMoveAssignBase<T>;
  using LocalBase::LocalBase;
  using LocalBase::_exists;
  using LocalBase::uncheckedGet;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const& noexcept -> T const& {
    return uncheckedGet();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator*()& noexcept -> T& {
    return uncheckedGet();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const&& noexcept -> T const&& {
    return cds::move(uncheckedGet());
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator*()&& noexcept -> T&& {
    return cds::move(uncheckedGet());
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator->() const noexcept -> T const* {
    return &uncheckedGet();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator->() noexcept -> T* {
    return &uncheckedGet();
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto hasValue() const noexcept -> bool {
    return _exists;
  }

  CDS_ATTR(3(nodiscard, explicit, constexpr(11))) operator bool() const {
    return _exists;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto get() const& CDS_ATTR(noexcept(false)) -> T const& {
    if (!_exists) {
      CDS_ATTR(throw(NoSuchElementException("Optional does not contain any value")));
    }
    return uncheckedGet();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto get()& CDS_ATTR(noexcept(false)) -> T& {
    if (!_exists) {
      CDS_ATTR(throw(NoSuchElementException("Optional does not contain any value")));
    }
    return uncheckedGet();
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto get() const&& CDS_ATTR(noexcept(false)) -> T const&& {
    if (!_exists) {
      CDS_ATTR(throw(NoSuchElementException("Optional does not contain any value")));
    }
    return cds::move(uncheckedGet());
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto get()&& CDS_ATTR(noexcept(false)) -> T&& {
    if (!_exists) {
      CDS_ATTR(throw(NoSuchElementException("Optional does not contain any value")));
    }
    return cds::move(uncheckedGet());
  }

  template <typename U> CDS_ATTR(2(nodiscard, constexpr(11))) auto getOr(U&& value) const&
  CDS_ATTR(noexcept(meta::IsNoexceptConstructible<T, U>::value))-> T {
    return _exists
        ? uncheckedGet()
        : static_cast<T>(cds::forward<U>(value));
  }

  template <typename U> CDS_ATTR(2(nodiscard, constexpr(14))) auto getOr(U&& value)&&
  CDS_ATTR(noexcept(meta::IsNoexceptConstructible<T, U>::value)) -> T {
    return _exists
        ? cds::move(uncheckedGet())
        : static_cast<T>(cds::forward<U>(value));
  }
};

template <typename> struct IsOptional : False {};
template <typename T> struct IsOptional<Optional<T>> : True {};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalMonadicBase : OptionalObservableBase<T> {
  using LocalBase = OptionalObservableBase<T>;
  using LocalBase::LocalBase;
  using LocalBase::_exists;
  using LocalBase::uncheckedGet;

  template <typename F, EnableIf<IsOptional<InvokeReturnOf<F, T const&>>> = 0> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto andThen(F&& function)
      const& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function), lvalue<T const>()))))
      -> InvokeReturnOf<F, T const&> {
    return _exists
        ? f::invoke(cds::forward<F>(function), uncheckedGet())
        : nullopt;
  }

  template <typename F, EnableIf<IsOptional<InvokeReturnOf<F, T&>>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto andThen(F&& function)& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function), lvalue<T>()))))
      -> InvokeReturnOf<F, T&> {
    return _exists
        ? f::invoke(cds::forward<F>(function), uncheckedGet())
        : nullopt;
  }

  template <typename F, EnableIf<IsOptional<InvokeReturnOf<F, T const&&>>> = 0> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto andThen(F&& function)
      const&& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function), rvalue<T const>()))))
      -> InvokeReturnOf<F, T const&&> {
    return _exists
        ? f::invoke(cds::forward<F>(function), cds::move(uncheckedGet()))
        : nullopt;
  }

  template <typename F, EnableIf<IsOptional<InvokeReturnOf<F, T&&>>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto andThen(F&& function)&& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function), rvalue<T>()))))
      -> InvokeReturnOf<F, T&&> {
    return _exists
        ? f::invoke(cds::forward<F>(function), cds::move(uncheckedGet()))
        : nullopt;
  }

  template <typename F, EnableIf<IsInvocable<F, T const&>> = 0> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transform(F&& function)
      const& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function), lvalue<T const>()))))
      -> Optional<InvokeReturnOf<F, T const&>> {
    return _exists
        ? Optional<InvokeReturnOf<F, T const&>>{f::invoke(cds::forward<F>(function), uncheckedGet())}
        : nullopt;
  }

  template <typename F, EnableIf<IsInvocable<F, T&>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transform(F&& function)& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function), lvalue<T>()))))
      -> Optional<InvokeReturnOf<F, T&>> {
    return _exists
        ? Optional<InvokeReturnOf<F, T&>>{f::invoke(cds::forward<F>(function), uncheckedGet())}
        : nullopt;
  }

  template <typename F, EnableIf<IsInvocable<F, T const&&>> = 0> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto transform(F&& function)
      const&& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function), rvalue<T const>()))))
      -> Optional<InvokeReturnOf<F, T const&&>> {
    return _exists
        ? Optional<InvokeReturnOf<F, T const&&>>{f::invoke(cds::forward<F>(function), cds::move(uncheckedGet()))}
        : nullopt;
  }

  template <typename F, EnableIf<IsInvocable<F, T&&>> = 0> CDS_ATTR(2(nodiscard, constexpr(14)))
  auto transform(F&& function)&& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function), rvalue<T>()))))
      -> Optional<InvokeReturnOf<F, T&&>> {
    return _exists
        ? Optional<InvokeReturnOf<F, T&&>>{f::invoke(cds::forward<F>(function), cds::move(uncheckedGet()))}
        : nullopt;
  }

  template <typename F, EnableIf<Or<IsSame<Optional<T>, InvokeReturnOf<F>>, IsSame<Nullopt, InvokeReturnOf<F>>>> = 0>
  auto orElse(F&& function) const& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function)))))
      -> Optional<T> {
    return _exists
        ? static_cast<Optional<T> const&>(*this)
        : f::invoke(cds::forward<F>(function));
  }

  template <typename F, EnableIf<Or<IsSame<Optional<T>, InvokeReturnOf<F>>, IsSame<Nullopt, InvokeReturnOf<F>>>> = 0>
  auto orElse(F&& function)&& CDS_ATTR(noexcept(noexcept(f::invoke(cds::forward<F>(function)))))
      -> Optional<T> {
    return _exists
        ? static_cast<Optional<T>&&>(cds::move(*this))
        : f::invoke(cds::forward<F>(function));
  }
};

template <typename T> struct CDS_ATTR(inheritsEBOs) OptionalBase : OptionalMonadicBase<T> {
  using LocalBase = OptionalMonadicBase<T>;
  using LocalBase::LocalBase;
};
} // namespace impl
} // namespace cds

#endif // CDS_PRIMITIVE_OPTIONAL_BASE_HPP
