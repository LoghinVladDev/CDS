//
// Created by loghin on 12/15/23.
//

#ifndef CDS_META_FUNCTION_TRAITS_HPP
#define CDS_META_FUNCTION_TRAITS_HPP
#pragma once

#include <cds/meta/ObjectTraits>
#include <cds/Utility>

namespace cds {
template <typename...> class Tuple {};
namespace meta {
namespace impl {
template <typename R, typename C, typename... A> struct MakeMemberFunctionTraits {
  using Return = R;
  using Class = C;
  using Args = Tuple<A...>;
};

template <typename T> struct InvokeCall {
  template <typename F, typename... A> static auto call(F&& f, A&&... a)
      noexcept -> decltype(cds::forward<F>(f)(cds::forward<A>(a)...));
};

template <typename C, typename MFn> struct InvokeCall<MFn C::*> {
  template <typename T, typename D = Decay<T>, typename = EnableIf<IsBaseOf<C, D>>> static auto get(T&& t)
      noexcept -> T&&;

  template <typename T, typename D = Decay<T>, typename = EnableIf<Not<IsBaseOf<C, D>>>> static auto get(T&& t)
      noexcept -> decltype(*cds::forward<T>(t));

  template <typename T, typename... A, typename RMFn, typename = EnableIf<IsFunction<RMFn>>> static auto call(
      RMFn C::* memFn, T&& obj, A&&... args
  ) noexcept -> decltype((get(cds::forward<T>(obj)).*memFn)(cds::forward<A>(args)...));

  template <typename T> static auto call(MFn C::*memFn, T&& obj) noexcept
      -> decltype(get(cds::forward<T>(obj)).*memFn);
};

template<typename Fn, typename... Args, typename DFn = meta::Decay<Fn>> auto invokeHint(
    Fn&& f, Args&&... args
) -> decltype(InvokeCall<DFn>::call(cds::forward<Fn>(f), cds::forward<Args>(args)...));

template<typename, typename, typename...> struct InvokeResult {};
template<typename Fn, typename...Args> struct InvokeResult<
    decltype(void(invokeHint(meta::rvalue<Fn>(), meta::rvalue<Args>()...))), Fn, Args...
> {
  using Type = decltype(invokeHint(meta::rvalue<Fn>(), meta::rvalue<Args>()...));
};

template <typename Fn, typename... Args> struct InvokeResultOf : InvokeResult<void, Fn, Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...), Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) volatile, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const volatile, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...)&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) volatile&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const volatile&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...)&&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const&&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) volatile&&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const volatile&&, Args...> : InvokeResult<void, R(Args...), Args...> {};

template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...), Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) volatile, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const volatile, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...)&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) volatile&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const volatile&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...)&&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const&&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) volatile&&, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const volatile&&, Args...> : InvokeResult<void, R(Args...), Args...> {};

template <typename> struct ReturnOf;
template <typename Fn, typename... Args> struct ReturnOf<Fn(Args...)> : InvokeResult<void, Fn(Args...), Args...> {};
template <typename Fn, typename... Args> struct ReturnOf<Fn(*)(Args...)> : InvokeResult<void, Fn(Args...), Args...> {};
template <typename Fn, typename... Args> struct ReturnOf<Fn(&)(Args...)> : InvokeResult<void, Fn(Args...), Args...> {};

template <typename R, typename... A> struct MakeFunctionTraits : MakeMemberFunctionTraits<R, void, A...> {};

template <typename T, typename = void> struct FunctionTraits {};
template <typename R, typename... A> struct FunctionTraits<auto(A...) -> R> : MakeFunctionTraits<R, A...> {};
template <typename R, typename... A> struct FunctionTraits<auto(*)(A...) -> R> : MakeFunctionTraits<R, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...)& -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const& -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile& -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile& -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...)&& -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const&& -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile&& -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile&& -> R> : MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) volatile -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const volatile -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...)& -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const& -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) volatile& -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const volatile& -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...)&& -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const&& -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) volatile&& -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const volatile&& -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
#if CDS_ATTR(noexcept_fn_type)
template <typename R, typename... A> struct FunctionTraits<auto(A...) noexcept -> R> : MakeFunctionTraits<R, A...> {};
template <typename R, typename... A> struct FunctionTraits<auto(*)(A...) noexcept -> R> : MakeFunctionTraits<R, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) noexcept-> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...)& noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const& noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile& noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile& noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...)&& noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const&& noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile&& noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile&& noexcept -> R> : MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) noexcept-> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) volatile noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const volatile noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...)& noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const& noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) volatile& noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const volatile& noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...)&& noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const&& noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) volatile&& noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};
template <typename R, typename C, typename... A> struct ReturnOf<auto(C::*)(A...) const volatile&& noexcept -> R> : InvokeResult<void, typename Member<auto(C::*)(A...) -> R>::Type, A...> {};

template <typename R, typename... Args> struct InvokeResultOf<R(Args...) noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) volatile noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const volatile noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...)& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) volatile& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const volatile& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...)&& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const&& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) volatile&& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename... Args> struct InvokeResultOf<R(Args...) const volatile&& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};

template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) volatile noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const volatile noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...)& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) volatile& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const volatile& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...)&& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const&& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) volatile&& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
template <typename R, typename C, typename... Args> struct InvokeResultOf<R(C::*)(Args...) const volatile&& noexcept, Args...> : InvokeResult<void, R(Args...), Args...> {};
#endif
} // namespace impl
template <typename Signature> struct FunctionTraits : impl::FunctionTraits<Decay<Signature>> {};

template <typename Signature> using ReturnOf = typename impl::ReturnOf<Signature>::Type;
template <typename Fn, typename... Args> using InvokeReturnOf = typename impl::InvokeResultOf<Fn, Args...>::Type;
template <typename Signature> using ClassOf = typename FunctionTraits<Signature>::Class;
template <typename Signature> using ArgsOf = typename FunctionTraits<Signature>::Args;
} // namespace meta
} // namespace cds

#endif // CDS_META_FUNCTION_TRAITS_HPP
