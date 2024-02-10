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
template <typename... Ts> auto consumerFunctionHint(Ts...) -> void;
template <typename R, typename... Ts> auto projectionFunctionHint(Ts...) -> R;
} // namespace impl

template <typename... Types> using PredicateFunction
    = decltype(&impl::predicateFunctionHint<Types...>);

template <typename... Types> using ConsumerFunction
    = decltype(&impl::consumerFunctionHint<Types...>);

template <typename R, typename... Types> using ProjectionFunction
    = decltype(&impl::projectionFunctionHint<R, Types...>);

namespace impl {
using meta::True;
using meta::False;
using meta::EnableIf;
using meta::Not;
using meta::IsSame;
using meta::IsClass;
using meta::Decay;
using meta::ReturnOf;
using meta::IsCallable;
using meta::InvokeReturnOf;
using meta::rvalue;

template <typename MFn> class MemberFunctionWrapper {
public:
  template <typename RMFn, EnableIf<Not<IsSame<Decay<RMFn>, MemberFunctionWrapper>>> = 0>
  CDS_ATTR(2(explicit, constexpr(11))) MemberFunctionWrapper(RMFn&& fn) noexcept : _fn(cds::forward<RMFn>(fn)) {}

  template <typename O, typename... Args> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(
      O&& obj, Args&&... args
  ) const CDS_ATTR(noexcept(noexcept((cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...))))
      -> EnableIf<IsClass<Decay<O>>, ReturnOf<MFn>> {
    return (cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...);
  }

private:
  CDS_ATTR(no_unique_address) MFn _fn;
};

template <typename Fn, typename = typename IsCallable<Fn>::Type> class NotFunctionWrapper {};

template <typename Fn> class NotFunctionWrapper<Fn, True> {
public:
  template <typename RFn, EnableIf<Not<IsSame<Decay<RFn>, NotFunctionWrapper>>> = 0>
  CDS_ATTR(2(explicit, constexpr(11))) NotFunctionWrapper(RFn&& fn) noexcept : _fn(cds::forward<RFn>(fn)) {}

  template <typename... Args> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(Args&&... args) const
      CDS_ATTR(noexcept(noexcept(_fn(cds::forward<Args>(args)...))))
      -> decltype(!rvalue<InvokeReturnOf<Fn, Args...>>()) {
    return !_fn(cds::forward<Args>(args)...);
  }

private:
  CDS_ATTR(no_unique_address) Fn _fn;
};

template <typename MFn> class NotFunctionWrapper<MFn, False> {
public:
  template <typename RMFn, EnableIf<Not<IsSame<Decay<RMFn>, NotFunctionWrapper>>> = 0>
  CDS_ATTR(2(explicit, constexpr(11))) NotFunctionWrapper(RMFn&& fn) noexcept : _fn(cds::forward<RMFn>(fn)) {}

  template <typename O, typename... Args> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(
      O&& obj, Args&&... args
  ) const CDS_ATTR(noexcept(noexcept((cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...))))
      -> EnableIf<IsClass<Decay<O>>, decltype(!(obj.*rvalue<MFn>())(cds::forward<Args>(args)...))> {
    return !(cds::forward<O>(obj).*_fn)(cds::forward<Args>(args)...);
  }

private:
  CDS_ATTR(no_unique_address) MFn _fn;
};
} // namespace impl

template <typename MemberFn> CDS_ATTR(2(nodiscard, constexpr(11))) auto memFn(MemberFn&& memberFn) noexcept
    -> impl::MemberFunctionWrapper<MemberFn> {
  return impl::MemberFunctionWrapper<MemberFn>(cds::forward<MemberFn>(memberFn));
}

template <typename Fn> CDS_ATTR(2(nodiscard, constexpr(11))) auto notFn(Fn&& fn) noexcept
    -> impl::NotFunctionWrapper<meta::Decay<Fn>> {
  return impl::NotFunctionWrapper<meta::Decay<Fn>>(cds::forward<Fn>(fn));
}
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_FUNCTIONAL_INTERFACE_HPP
