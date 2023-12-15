//
// Created by loghin on 12/14/23.
//

#ifndef CDS_FUNCTIONAL_FUNCTIONAL_INTERFACE_HPP
#define CDS_FUNCTIONAL_FUNCTIONAL_INTERFACE_HPP
#pragma once

#include <cds/Utility>
#include <cds/meta/FunctionTraits>

namespace cds {
namespace functional {
namespace impl {
template <typename... Ts> auto predicateFunctionHint(Ts...) -> bool;
template <typename R, typename... Ts> auto mapperFunctionHint(Ts...) -> R;
} // namespace impl

template <typename... Types> using PredicateFunction = decltype(&impl::predicateFunctionHint<Types...>);
template <typename R, typename... Types> using MapperFunction = decltype(&impl::mapperFunctionHint<R, Types...>);

template <typename R, typename C, typename... Ts> using MemberFunction = R(C::*)(Ts...);
template <typename R, typename C, typename... Ts> using ConstMemberFunction = R(C::*)(Ts...) const;
template <typename R, typename C, typename... Ts> using MemberFunctionLVal = R(C::*)(Ts...)&;
template <typename R, typename C, typename... Ts> using ConstMemberFunctionLVal = R(C::*)(Ts...) const&;
template <typename R, typename C, typename... Ts> using MemberFunctionRVal = R(C::*)(Ts...)&&;

namespace impl {
template <typename MFn> struct MemberFunctionWrapper {
  template <typename RMFn, meta::EnableIf<meta::Not<meta::IsSame<meta::Decay<RMFn>, MemberFunctionWrapper>>> = 0>
  CDS_ATTR(2(explicit, constexpr(11))) MemberFunctionWrapper(RMFn&& fn) noexcept : _fn(cds::forward<MFn>(fn)) {}

  template <typename O, typename... Args> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(
      O&& obj, Args&&... args
  ) const noexcept(noexcept((cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...))) -> meta::ReturnOf<MFn> {
    return (cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...);
  }

  MFn _fn {nullptr};
};
} // namespace impl

template <typename MemberFn> CDS_ATTR(2(nodiscard, constexpr(11))) auto memFn(MemberFn&& memberFn) noexcept
    -> impl::MemberFunctionWrapper<MemberFn> {
  return impl::MemberFunctionWrapper<MemberFn>{cds::forward<MemberFn>(memberFn)};
}
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_FUNCTIONAL_INTERFACE_HPP
