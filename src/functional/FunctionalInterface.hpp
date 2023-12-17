//
// Created by loghin on 12/14/23.
//

#ifndef CDS_FUNCTIONAL_FUNCTIONAL_INTERFACE_HPP
#define CDS_FUNCTIONAL_FUNCTIONAL_INTERFACE_HPP
#pragma once

#include <cds/meta/FunctionTraits>

namespace cds {
namespace functional {
namespace impl {
template <typename... Ts> auto predicateFunctionHint(Ts...) -> bool;
template <typename R, typename... Ts> auto mapperFunctionHint(Ts...) -> R;
} // namespace impl

template <typename... Types> using PredicateFunction = decltype(&impl::predicateFunctionHint<Types...>);
template <typename R, typename... Types> using MapperFunction = decltype(&impl::mapperFunctionHint<R, Types...>);

namespace impl {
template <typename MFn> struct MemberFunctionWrapper {
  template <typename RMFn, meta::EnableIf<meta::Not<meta::IsSame<meta::Decay<RMFn>, MemberFunctionWrapper>>> = 0>
  CDS_ATTR(2(explicit, constexpr(11))) MemberFunctionWrapper(RMFn&& fn) noexcept : _fn(cds::forward<RMFn>(fn)) {}

  template <typename O, typename... Args> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(
      O&& obj, Args&&... args
  ) const CDS_ATTR(noexcept(noexcept((cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...)))) -> meta::ReturnOf<MFn> {
    return (cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...);
  }

  MFn _fn {nullptr};
};

template <typename Fn, bool = meta::IsCallable<Fn>::value> struct NotFunctionWrapper {};

template <typename Fn> struct NotFunctionWrapper<Fn, true> {
  template <typename RFn, meta::EnableIf<meta::Not<meta::IsSame<meta::Decay<RFn>, NotFunctionWrapper>>> = 0>
  CDS_ATTR(2(explicit, constexpr(11))) NotFunctionWrapper(RFn&& fn) noexcept : _fn(cds::forward<RFn>(fn)) {}

  template <typename... Args> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(Args&&... args) const
      CDS_ATTR(noexcept(noexcept(_fn(cds::forward<Args>(args)...)))) -> decltype(!meta::value<meta::InvokeReturnOf<Fn, Args...>>()) {
    return !_fn(cds::forward<Args>(args)...);
  }

  Fn _fn {nullptr};
};

template <typename MFn> struct NotFunctionWrapper<MFn, false> {
  template <typename RMFn, meta::EnableIf<meta::Not<meta::IsSame<meta::Decay<RMFn>, NotFunctionWrapper>>> = 0>
  CDS_ATTR(2(explicit, constexpr(11))) NotFunctionWrapper(RMFn&& fn) noexcept : _fn(cds::forward<RMFn>(fn)) {}

  template <typename O, typename... Args> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(
      O&& obj, Args&&... args
  ) const CDS_ATTR(noexcept(noexcept((cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...))))
      -> decltype(!(obj.*meta::value<MFn>())(cds::forward<Args>(args)...)) {
    return !(cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...);
  }

  MFn _fn {nullptr};
};
} // namespace impl

template <typename MemberFn> CDS_ATTR(2(nodiscard, constexpr(11))) auto memFn(MemberFn&& memberFn) noexcept
    -> impl::MemberFunctionWrapper<MemberFn> {
  return impl::MemberFunctionWrapper<MemberFn>{cds::forward<MemberFn>(memberFn)};
}

template <typename Fn> CDS_ATTR(2(nodiscard, constexpr(11))) auto notFn(Fn&& fn) noexcept
    -> impl::NotFunctionWrapper<meta::Decay<Fn>> {
  return impl::NotFunctionWrapper<meta::Decay<Fn>>(cds::forward<Fn>(fn));
}
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_FUNCTIONAL_INTERFACE_HPP
