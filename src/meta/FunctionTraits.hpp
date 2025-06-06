//
// Created by loghin on 12/15/23.
//

#ifndef CDS_META_FUNCTION_TRAITS_HPP
#define CDS_META_FUNCTION_TRAITS_HPP
#pragma once

#include <cds/meta/ObjectTraits>
#include <cds/meta/Semantics>

namespace cds {
namespace impl {
template <typename...> class Tuple;
} // namespace impl
namespace meta {
namespace impl {
template <typename R, typename C, typename... A> struct MakeMemberFunctionTraits {
    using Return = R;
    using Class = C;
    using Args = cds::impl::Tuple<A...>;
};

template <typename R, typename... A> struct MakeFunctionTraits : MakeMemberFunctionTraits<R, void, A...> {};

template <typename, typename = void> struct FunctionTraits {};
template <typename R, typename... A> struct FunctionTraits<auto(A...) -> R> : MakeFunctionTraits<R, A...> {};
template <typename R, typename... A> struct FunctionTraits<auto(*)(A...) -> R> : MakeFunctionTraits<R, A...> {};
template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...)& -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const& -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile& -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile& -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...)&& -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const&& -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile&& -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile&& -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

#if CDS_ATTR(noexcept_fn_type)
template <typename R, typename... A> struct FunctionTraits<auto(A...) noexcept -> R> : MakeFunctionTraits<R, A...> {};
template <typename R, typename... A> struct FunctionTraits<auto(*)(A...) noexcept -> R> :
    MakeFunctionTraits<R, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) noexcept-> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...)& noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const& noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile& noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile& noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...)&& noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const&& noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) volatile&& noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};

template <typename R, typename C, typename... A> struct FunctionTraits<auto(C::*)(A...) const volatile&& noexcept -> R> :
    MakeMemberFunctionTraits<R, C, A...> {};
#endif // #if CDS_ATTR(noexcept_fn_type)

template <typename F, typename = typename IsMember<RemoveCVRef<F>>::Type, typename = void> struct Invoke {};

template <typename T> struct Invoke<T, False> {
  template <typename F, typename... A>
  CDS_ATTR(constexpr(11)) static auto call(F&& f, A&&... a) CDS_ATTR(noexcept(
      noexcept(fwd<F>(f)(fwd<A>(a)...))
  )) -> decltype(fwd<F>(f)(fwd<A>(a)...)) {
    return fwd<F>(f)(fwd<A>(a)...);
  }
};

template <
    typename F,
    typename T,
    typename = typename IsPointer<RemoveCVRef<T>>::Type,
    typename = typename IsFunction<typename Member<F>::Type>::Type
> struct MemberInvoke {};

template <typename F, typename T> struct MemberInvoke<F, T, False, True> {
  template <typename F0, typename O, typename... A>
  CDS_ATTR(constexpr(11)) static auto call(F0&& f, O&& obj, A&&... a) CDS_ATTR(noexcept(
      noexcept((fwd<O>(obj).*fwd<F0>(f))(fwd<A>(a)...))
  )) -> decltype((fwd<O>(obj).*fwd<F0>(f))(fwd<A>(a)...)) {
    return (fwd<O>(obj).*fwd<F0>(f))(fwd<A>(a)...);
  }
};

template <typename F, typename T> struct MemberInvoke<F, T, True, True> {
  template <typename F0, typename O, typename... A>
  CDS_ATTR(constexpr(11)) static auto call(F0&& f, O&& obj, A&&... a) CDS_ATTR(noexcept(
      noexcept((fwd<O>(obj)->*fwd<F0>(f))(fwd<A>(a)...))
  )) -> decltype((fwd<O>(obj)->*fwd<F0>(f))(fwd<A>(a)...)) {
    return (fwd<O>(obj)->*fwd<F0>(f))(fwd<A>(a)...);
  }
};

template <typename F, typename T> struct MemberInvoke<F, T, False, False> {
  template <typename F0, typename O>
  CDS_ATTR(constexpr(11)) static auto call(F0&& f, O&& obj) CDS_ATTR(noexcept(
      noexcept(fwd<O>(obj).*fwd<F0>(f))
  )) -> decltype(fwd<O>(obj).*fwd<F0>(f)) {
    return fwd<O>(obj).*fwd<F0>(f);
  }
};

template <typename F, typename T> struct MemberInvoke<F, T, True, False> {
  template <typename F0, typename O>
  CDS_ATTR(constexpr(11)) static auto call(F0&& f, O&& obj) CDS_ATTR(noexcept(
      noexcept(fwd<O>(obj)->*fwd<F0>(f))
  )) -> decltype(fwd<O>(obj)->*fwd<F0>(f)) {
    return fwd<O>(obj)->*fwd<F0>(f);
  }
};

template <typename T> struct Invoke<T, True> {
  template <typename F, typename O, typename... A>
  CDS_ATTR(constexpr(11)) static auto call(F&& f, O&& obj, A&&... a) CDS_ATTR(noexcept(
      noexcept(MemberInvoke<RemoveCVRef<F>, O>::call(fwd<F>(f), fwd<O>(obj), fwd<A>(a)...))
  )) -> decltype(
      MemberInvoke<RemoveCVRef<F>, O>::call(fwd<F>(f), fwd<O>(obj), fwd<A>(a)...)
  ) {
    return MemberInvoke<RemoveCVRef<F>, O>::call(fwd<F>(f), fwd<O>(obj), fwd<A>(a)...);
  }
};

// TODO: Remove?
template <typename Fn, typename = typename meta::IsMember<RemoveCVRef<Fn>>::Type> struct FunctionRValue {};
template <typename Fn> struct FunctionRValue<Fn, meta::True> {
  using Type = meta::Member<Fn>;
};

template <typename Fn> struct FunctionRValue<Fn, meta::False> {
  using Type = Fn;
};

template <typename, typename = void> struct InvokeTraits : meta::False {
  using Noexcept = False;
};

template <typename Fn, typename... Args>
struct InvokeTraits<Pack<Fn, Args...>, Void<decltype(Invoke<Fn>::call(rvalue<Fn>(), rvalue<Args>()...))>> : meta::True {
  using ReturnType = decltype(Invoke<Fn>::call(rvalue<Fn>(), meta::rvalue<Args>()...));
  using Noexcept = Bool<noexcept(Invoke<Fn>::call(rvalue<Fn>(), meta::rvalue<Args>()...))>;
};
} // namespace impl
template <typename Signature> struct FunctionTraits : impl::FunctionTraits<Decay<Signature>> {};

template <typename Fn, typename... Args> using InvokeReturnOf =
    typename impl::InvokeTraits<impl::Pack<Fn, Args...>>::ReturnType;

template <typename Fn, typename... Args> using IsInvocable =
    typename impl::InvokeTraits<impl::Pack<Fn, Args...>>::Type;

template <typename Fn, typename... Args> using IsNoexceptInvocable =
    typename impl::InvokeTraits<impl::Pack<Fn, Args...>>::Type;

template <typename Signature> using ReturnOf = typename FunctionTraits<Signature>::Return;
template <typename Signature> using ClassOf = typename FunctionTraits<Signature>::Class;
template <typename Signature> using ArgsOf = typename FunctionTraits<Signature>::Args;
} // namespace meta
} // namespace cds

#endif // CDS_META_FUNCTION_TRAITS_HPP
