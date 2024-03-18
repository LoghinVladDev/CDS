//
// Created by loghin on 12/15/23.
//

#ifndef CDS_META_FUNCTION_TRAITS_HPP
#define CDS_META_FUNCTION_TRAITS_HPP
#pragma once

#include <cds/meta/ObjectTraits>
#include <cds/meta/Semantics>

namespace cds {
template <typename...> class Tuple {};
namespace meta {
namespace impl {
template <typename R, typename C, typename... A> struct MakeMemberFunctionTraits {
    using Return = R;
    using Class = C;
    using Args = Tuple<A...>;
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
        noexcept(cds::forward<F>(f)(cds::forward<A>(a)...))
    )) -> decltype(cds::forward<F>(f)(cds::forward<A>(a)...)) {
        return cds::forward<F>(f)(cds::forward<A>(a)...);
    }
};

template <typename T, typename = typename IsPointer<RemoveCVRef<T>>::Type> struct MemberInvoke {};

template <typename T> struct MemberInvoke<T, False> {
    template <typename F, typename O, typename... A>
    CDS_ATTR(constexpr(11)) static auto call(F&& f, O&& obj, A&&... a) CDS_ATTR(noexcept(
        noexcept((cds::forward<O>(obj).*cds::forward<F>(f))(cds::forward<A>(a)...))
    )) -> decltype((cds::forward<O>(obj).*cds::forward<F>(f))(cds::forward<A>(a)...)) {
        return (cds::forward<O>(obj).*cds::forward<F>(f))(cds::forward<A>(a)...);
    }
};

template <typename T> struct MemberInvoke<T, True> {
    template <typename F, typename O, typename... A>
    CDS_ATTR(constexpr(11)) static auto call(F&& f, O&& obj, A&&... a) CDS_ATTR(noexcept(
        noexcept((cds::forward<O>(obj)->*cds::forward<F>(f))(cds::forward<A>(a)...))
    )) -> decltype((cds::forward<O>(obj)->*cds::forward<F>(f))(cds::forward<A>(a)...)) {
        return (cds::forward<O>(obj)->*cds::forward<F>(f))(cds::forward<A>(a)...);
    }
};

template <typename T> struct Invoke<T, True> {
    template <typename F, typename O, typename... A>
    CDS_ATTR(constexpr(11)) static auto call(F&& f, O&& obj, A&&... a) CDS_ATTR(noexcept(
        noexcept(MemberInvoke<O>::call(cds::forward<F>(f), cds::forward<O>(obj), cds::forward<A>(a)...))
    )) -> decltype(MemberInvoke<O>::call(cds::forward<F>(f), cds::forward<O>(obj), cds::forward<A>(a)...)) {
        return MemberInvoke<O>::call(cds::forward<F>(f), cds::forward<O>(obj), cds::forward<A>(a)...);
    }
};

template <typename Fn, typename = typename meta::IsMember<RemoveCVRef<Fn>>::Type> struct FunctionRValue {};
template <typename Fn> struct FunctionRValue<Fn, meta::True> {
  using Type = meta::Member<Fn>;
};

template <typename Fn> struct FunctionRValue<Fn, meta::False> {
  using Type = Fn;
};

template <typename, typename = void> struct InvokeTraits : meta::False {
  using ReturnType = void;
};

template <typename Fn, typename... Args>
struct InvokeTraits<
    Pack<Fn, Args...>,
    Void<decltype(Invoke<typename FunctionRValue<Fn>::Type>::call(
        rvalue<typename FunctionRValue<Fn>::Type>(), rvalue<Args>()...)
    )>
> : meta::True {
  using ReturnType = decltype(Invoke<typename FunctionRValue<Fn>::Type>::call(
      rvalue<typename FunctionRValue<Fn>::Type>(), meta::rvalue<Args>()...)
  );
};
} // namespace impl
template <typename Signature> struct FunctionTraits : impl::FunctionTraits<Decay<Signature>> {};

template <typename Fn, typename... Args> using InvokeReturnOf =
    typename impl::InvokeTraits<impl::Pack<Fn, Args...>>::ReturnType;

template <typename Fn, typename... Args> using IsInvocable =
    typename impl::InvokeTraits<impl::Pack<Fn, Args...>>::Type;

template <typename Signature> using ReturnOf = typename FunctionTraits<Signature>::Return;
template <typename Signature> using ClassOf = typename FunctionTraits<Signature>::Class;
template <typename Signature> using ArgsOf = typename FunctionTraits<Signature>::Args;
} // namespace meta
} // namespace cds

#endif // CDS_META_FUNCTION_TRAITS_HPP
