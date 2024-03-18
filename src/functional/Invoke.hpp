//
// Created by loghin on 2/10/24.
//

#ifndef CDS_FUNCTIONAL_INVOKE_HPP
#define CDS_FUNCTIONAL_INVOKE_HPP
#pragma once

#include <cds/meta/FunctionTraits>

namespace cds {
namespace functional {
template <typename F, typename... A> CDS_ATTR(constexpr(11)) auto invoke(F&& function, A&&... arguments)
    CDS_ATTR(noexcept(noexcept(meta::impl::Invoke<F>::call(cds::forward<F>(function), cds::forward<A>(arguments)...))))
    -> decltype(meta::impl::Invoke<F>::call(cds::forward<F>(function), cds::forward<A>(arguments)...)) {
  return meta::impl::Invoke<F>::call(cds::forward<F>(function), cds::forward<A>(arguments)...);
}
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_INVOKE_HPP
