//
// Created by loghin on 2/10/24.
//

#ifndef CDS_FUNCTIONAL_INVOKE_HPP
#define CDS_FUNCTIONAL_INVOKE_HPP
#pragma once

#include <cds/meta/FunctionTraits>

namespace cds {
namespace functional {
namespace impl {
using meta::impl::Invoke;

template <typename F, typename... A> CDS_ATTR(constexpr(11)) auto invoke(F&& function, A&&... arguments)
    CDS_ATTR(noexcept(noexcept(Invoke<F>::call(fwd<F>(function), fwd<A>(arguments)...))))
    -> decltype(Invoke<F>::call(fwd<F>(function), fwd<A>(arguments)...)) {
  return Invoke<F>::call(fwd<F>(function), fwd<A>(arguments)...);
}
} // namespace impl

using impl::invoke;
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_INVOKE_HPP
