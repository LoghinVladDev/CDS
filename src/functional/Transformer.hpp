//
// Created by loghin on 12/22/23.
//

#ifndef CDS_FUNCTIONAL_TRANSFORMER_HPP
#define CDS_FUNCTIONAL_TRANSFORMER_HPP

#include <cds/meta/Semantics>

namespace cds {
namespace functional {
namespace impl {
using meta::EnableIf;
using meta::Ge;
using meta::Lt;
using meta::Int;

template<typename T = void> struct Identity {
  template <typename T1 = T, EnableIf<Ge<Int<sizeof(T1)>, Int<sizeof(Size)>>>>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto identity(T const &v) noexcept -> T const& { return v; }

  template <typename T1 = T, EnableIf<Lt<Int<sizeof(T1)>, Int<sizeof(Size)>>>>
  CDS_ATTR(2(nodiscard, constexpr(11))) auto identity(T v) noexcept -> T { return v; }
};

template <> struct Identity<void> {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11))) auto identity(T&& v) noexcept -> T&& {
    return cds::forward<T>(v);
  }
};
} // namespace impl
} // namespace functional
} // namespace cds

#endif // CDS_FUNCTIONAL_TRANSFORMER_HPP
