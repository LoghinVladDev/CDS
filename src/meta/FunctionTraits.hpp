//
// Created by loghin on 12/15/23.
//

#ifndef CDS_META_FUNCTION_TRAITS_HPP
#define CDS_META_FUNCTION_TRAITS_HPP
#pragma once

#include <cds/meta/Compiler>

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
#endif
} // namespace impl

template <typename Signature> struct FunctionTraits : impl::FunctionTraits<Signature> {};

template <typename Signature> using ReturnOf = typename FunctionTraits<Signature>::Return;
template <typename Signature> using ClassOf = typename FunctionTraits<Signature>::Class;
template <typename Signature> using ArgsOf = typename FunctionTraits<Signature>::Args;
} // namespace meta
} // namespace cds

#endif // CDS_META_FUNCTION_TRAITS_HPP
