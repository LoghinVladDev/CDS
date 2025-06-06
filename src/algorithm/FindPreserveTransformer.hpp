//
// Created by loghin on 6/3/25.
//

#ifndef CDS_ALGORITHM_FIND_PRESERVE_TRANSFORMER_HPP
#define CDS_ALGORITHM_FIND_PRESERVE_TRANSFORMER_HPP
#pragma once

#include <cds/meta/Semantics>

namespace cds {
namespace impl {
using meta::rvalue;

template <typename = void> struct FindPreserveTransformer {
  template <typename IB, typename IE, typename I> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(CDS_ATTR(unused) IB&& b, CDS_ATTR(unused) IE&& e, I&& i) const noexcept -> I {
    return fwd<I>(i);
  }
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_ALGORITHM_FIND_PRESERVE_TRANSFORMER_HPP
