//
// Created by loghin on 8/24/25.
//

#ifndef CDS_FUNCTIONAL_FUNCTION_REF_BASE_HPP
#define CDS_FUNCTIONAL_FUNCTION_REF_BASE_HPP
#pragma once

#include <cds/meta/FunctionTraits>
#include <cds/meta/Semantics>

namespace cds {
namespace functional {
namespace impl {
using meta::Bool;
using meta::Conditional;
using meta::DoesNotHide;
using meta::InvokeReturnOf;
using meta::IsConvertible;
using meta::IsSame;
using meta::IsVoid;
using meta::Null;
using meta::Or;
using meta::RemoveRef;
using meta::Requires;
using meta::rvalue;

enum class BoolTrait {
  True,
  False,
  Unknown
};

struct FunctionPointer{};
struct Functor{};

template <BoolTrait /* IsConst */> union FunctionRefStorage;

template <> union FunctionRefStorage<BoolTrait::False> {
  using ErasedFunctor = void*;
  using ErasedFunctionPointer = void(*)();

  template <typename F> CDS_ATTR(2(explicit, constexpr(26))) FunctionRefStorage(FunctionPointer, F&& ptr) noexcept :
      functionPointer{reinterpret_cast<ErasedFunctionPointer>(fwd<F>(ptr))} {}

  template <typename F> CDS_ATTR(2(explicit, constexpr(26))) FunctionRefStorage(Functor, F& functor) noexcept :
      functor{static_cast<ErasedFunctor>(&functor)} {}

  ErasedFunctor functor;
  ErasedFunctionPointer functionPointer;
};

template <> union FunctionRefStorage<BoolTrait::True> {
  using ErasedFunctor = void const*;
  using ErasedFunctionPointer = void(* const)();

  template <typename F> CDS_ATTR(2(explicit, constexpr(26))) FunctionRefStorage(FunctionPointer, F&& ptr) noexcept :
      functionPointer{reinterpret_cast<ErasedFunctionPointer>(fwd<F>(ptr))} {}

  template <typename F> CDS_ATTR(2(explicit, constexpr(26))) FunctionRefStorage(Functor, F const& functor) noexcept :
      functor{static_cast<ErasedFunctor>(&functor)} {}

  ErasedFunctor functor;
  ErasedFunctionPointer functionPointer;
};

template <typename R0, typename R1> struct IsCompatibleReturnType : Or<
    IsVoid<R0>,
    IsSame<R0, R1>,
    IsConvertible<R0, R1>
> {};

template <typename Callable, typename R, typename... A>
struct IsCompatibleCallable : IsCompatibleReturnType<InvokeReturnOf<Callable, A...>, R> {};

template <typename Callable, BoolTrait isConstFn> struct FunctionRefCallableTraits {
  using Tag = Functor;
  using Storage = FunctionRefStorage<isConstFn>;
  using ActualCallable = Conditional<Bool<isConstFn == BoolTrait::True>, Callable const, Callable>;

  template <typename R0, typename... A0> CDS_ATTR(constexpr(26)) static auto invoker(Storage storage, A0... args)
      CDS_ATTR(noexcept(noexcept(rvalue<ActualCallable>()(fwd<A0>(args)...)))) -> R0 {
    return static_cast<R0>((*static_cast<ActualCallable*>(storage.functor))(fwd<A0>(args)...));
  }
};

template <typename R, typename... A, BoolTrait isConstFn> struct FunctionRefCallableTraits<R(*)(A...), isConstFn> {
  using Tag = FunctionPointer;
  using Storage = FunctionRefStorage<isConstFn>;

  template <typename R0, typename... A0> CDS_ATTR(constexpr(26)) static auto invoker(Storage storage, A0... args)
      CDS_ATTR(noexcept(noexcept(rvalue<R(*)(A...)>()(fwd<A0>(args)...)))) -> R0 {
    return static_cast<R0>(reinterpret_cast<R(*)(A...)>(storage.functionPointer)(fwd<A0>(args)...));
  }
};

template <typename R, typename... A, BoolTrait isConstFn> struct FunctionRefCallableTraits<R(A...), isConstFn> {
  using Tag = FunctionPointer;
  using Storage = FunctionRefStorage<isConstFn>;

  template <typename R0, typename... A0> CDS_ATTR(constexpr(26)) static auto invoker(Storage storage, A0... args)
      CDS_ATTR(noexcept(noexcept(rvalue<R(*)(A...)>()(fwd<A0>(args)...)))) -> R0 {
    return static_cast<R0>(reinterpret_cast<R(*)(A...)>(storage.functionPointer)(fwd<A0>(args)...));
  }
};

template <BoolTrait isConstFn, typename R, typename... A> class FunctionRefStorageBase {
  using Storage = FunctionRefStorage<isConstFn>;
  using Invoker = R(*)(Storage, A...);

public:
  template <
      typename Callable,
      typename = Requires<DoesNotHide<FunctionRefStorageBase, Callable>>,
      typename = Requires<IsCompatibleCallable<Callable, R, A...>>,
      typename Traits = FunctionRefCallableTraits<RemoveRef<Callable>, isConstFn>
  > CDS_ATTR(2(implicit, constexpr(26))) FunctionRefStorageBase(Callable&& callable) noexcept :
      _storage{typename Traits::Tag{}, callable},
      _invoker{&Traits::template invoker<R, A...>} {}

  FunctionRefStorageBase(FunctionRefStorageBase const& functionRef) = default;
  auto operator=(FunctionRefStorageBase const& functionRef) noexcept -> FunctionRefStorageBase& = default;

  FunctionRefStorageBase(Null) = delete;
  auto operator=(Null) -> FunctionRefStorageBase& = delete;

  template <typename T> auto operator=(T) -> FunctionRefStorageBase = delete;

protected:
  CDS_ATTR(constexpr(11)) auto invoker() const noexcept -> Invoker {
    return _invoker;
  }

  CDS_ATTR(constexpr(11)) auto storage() const noexcept -> Storage {
    return _storage;
  }

private:
  Storage _storage;
  Invoker _invoker;
};

template <
    BoolTrait /* isConstFn */, BoolTrait /* isNoexceptFn */, BoolTrait /* isNoDiscardFn */,
    typename R, typename... A
> class FunctionRefInvokeBase;

template <BoolTrait isConstFn, typename R, typename... A>
class FunctionRefInvokeBase<isConstFn, BoolTrait::Unknown, BoolTrait::False, R, A...> :
    public FunctionRefStorageBase<isConstFn, R, A...> {
  using Base = FunctionRefStorageBase<isConstFn, R, A...>;
  using Base::invoker;
  using Base::storage;

public:
  using Base::Base;
  using Base::operator=;

  template <typename... A0> CDS_ATTR(constexpr(26)) auto operator()(A0&&... args) const -> R {
    return invoker()(storage(), fwd<A0>(args)...);
  }
};

template <BoolTrait isConstFn, typename R, typename... A>
class FunctionRefInvokeBase<isConstFn, BoolTrait::True, BoolTrait::False, R, A...> :
    public FunctionRefStorageBase<isConstFn, R, A...> {
  using Base = FunctionRefStorageBase<isConstFn, R, A...>;
  using Base::invoker;
  using Base::storage;

public:
  using Base::Base;
  using Base::operator=;

  template <typename... A0> CDS_ATTR(constexpr(26)) auto operator()(A0&&... args) const noexcept -> R {
    return invoker()(storage(), fwd<A0>(args)...);
  }
};

template <BoolTrait isConstFn, typename R, typename... A>
class FunctionRefInvokeBase<isConstFn, BoolTrait::Unknown, BoolTrait::True, R, A...> :
    public FunctionRefStorageBase<isConstFn, R, A...> {
  using Base = FunctionRefStorageBase<isConstFn, R, A...>;
  using Base::invoker;
  using Base::storage;

public:
  using Base::Base;
  using Base::operator=;

  template <typename... A0> CDS_ATTR(2(nodiscard, constexpr(26))) auto operator()(A0&&... args) const -> R {
    return invoker()(storage(), fwd<A0>(args)...);
  }
};

template <BoolTrait isConstFn, typename R, typename... A>
class FunctionRefInvokeBase<isConstFn, BoolTrait::True, BoolTrait::True, R, A...> :
    public FunctionRefStorageBase<isConstFn, R, A...> {
  using Base = FunctionRefStorageBase<isConstFn, R, A...>;
  using Base::invoker;
  using Base::storage;

public:
  using Base::Base;
  using Base::operator=;

  template <typename... A0> CDS_ATTR(2(nodiscard, constexpr(26))) auto operator()(A0&&... args) const noexcept -> R {
    return invoker()(storage(), fwd<A0>(args)...);
  }
};

template <BoolTrait isConstFn, BoolTrait isNoexceptFn, BoolTrait isNoDiscardFn, typename R, typename... A>
class FunctionRefBase : public FunctionRefInvokeBase<isConstFn, isNoexceptFn, isNoDiscardFn, R, A...> {
  using Base = FunctionRefInvokeBase<isConstFn, isNoexceptFn, isNoDiscardFn, R, A...>;
public:
  using Base::Base;
  using Base::operator=;
};
} // namespace impl
} // namespace functional
} // namespace cds

#endif // #ifndef CDS_FUNCTIONAL_FUNCTION_REF_BASE_HPP
