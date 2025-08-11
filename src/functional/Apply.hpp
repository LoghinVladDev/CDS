//
// Created by loghin on 8/11/25.
//

#ifndef CDS_FUNCTIONAL_APPLY_HPP
#define CDS_FUNCTIONAL_APPLY_HPP
#pragma once

#include <cds/functional/Invoke>
#include <cds/meta/Base>

#include "../stdlib/utility.hpp"

namespace cds {
namespace functional {
namespace impl {
using meta::Bool;
using meta::False;
using meta::MakeIndexSequence;
using meta::IndexSequence;
using meta::RemoveCVRef;
using meta::ReplicateCVRef;
using meta::True;
using meta::Void;
using meta::rvalue;
using meta::value;

namespace fn = functional;

template <typename T, typename = void> struct IsTupleLike : False {};
template <typename T> struct IsTupleLike<T, Void<decltype(std::tuple_size<T>::value)>> : True {};

template <typename T, typename = typename IsTupleLike<T>::Type> struct Apply {
  template <typename T0> auto operator()(T0&&) const noexcept -> void {
    static_assert(IsTupleLike<T>::value, "Given type does not satisfy tuple-like");
  }
};

template <typename T, Size size, typename = MakeIndexSequence<size>> struct ApplyWithIs;

template <typename T, Size size, unsigned... indices> struct ApplyWithIs<T, size, IndexSequence<indices...>> {
  template <typename F, typename T0> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator()(F&& fn, T0&& tupleLike) const
      CDS_ATTR(noexcept(noexcept(fn::invoke(fwd<F>(fn), value<ReplicateCVRef<T0, typename std::tuple_element<indices, T>::type>>()...))))
      -> decltype(fn::invoke(fwd<F>(fn), value<ReplicateCVRef<T0, typename std::tuple_element<indices, T>::type>>()...)) {
    return fn::invoke(fwd<F>(fn), get<indices>(fwd<T0>(tupleLike))...);
  }
};

template <typename T> struct Apply<T, True> : ApplyWithIs<T, std::tuple_size<T>::value> {};

template <typename F, typename T, typename DT = RemoveCVRef<T>> CDS_ATTR(2(nodiscard, constexpr(11)))
auto apply(F&& function, T&& tupleLike) CDS_ATTR(noexcept(noexcept(Apply<DT>{}(fwd<F>(function), fwd<T>(tupleLike)))))
    -> decltype(Apply<DT>{}(fwd<F>(function), fwd<T>(tupleLike))) {
  return Apply<DT>{}(fwd<F>(function), fwd<T>(tupleLike));
}

template <typename F, typename T, typename = void> struct ApplyTraits : False {};

template <typename F, typename T> struct ApplyTraits<F, T, Void<decltype(impl::apply(rvalue<F>(), value<T>()))>> : True {
  using Return = decltype(impl::apply(rvalue<F>(), meta::value<T>()));
  using Noexcept = Bool<noexcept(impl::apply(rvalue<F>(), meta::value<T>()))>;
};
} // namespace impl

using impl::apply;
} // namespace functional

namespace meta {
template <typename F, typename T> using ApplyReturnOf = typename functional::impl::ApplyTraits<F, T>::Return;
template <typename F, typename T> using IsAppliable = typename functional::impl::ApplyTraits<F, T>::Type;
template <typename F, typename T> using IsNoexceptAppliable = typename functional::impl::ApplyTraits<F, T>::Noexcept;
} // namespace meta
} // namespace cds

#endif // #ifndef CDS_FUNCTIONAL_APPLY_HPP
