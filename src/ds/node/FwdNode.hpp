//
// Created by loghin on 2/7/24.
//

#ifndef CDS_DS_FWD_NODE_HPP
#define CDS_DS_FWD_NODE_HPP
#pragma once

#include <cds/meta/Semantics>

namespace cds {
namespace impl {
template <typename T> struct FwdNode {
  FwdNode* next;
  T data;

  template <typename... A> CDS_ATTR(2(explicit, constexpr(11))) FwdNode(FwdNode* n, A&&... args)
      CDS_ATTR(noexcept(noexcept(T(fwd<A>(args)...)))) : next{n}, data{fwd<A>(args)...} {}
};

template <typename P = void> struct FwdNodeDataProjection : P {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(FwdNode<T> const& node) const noexcept -> decltype(P{}(node.data)) {
    return static_cast<P const&>(*this)(node.data);
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(FwdNode<T>& node) const noexcept -> decltype(P{}(node.data)) {
    return static_cast<P const&>(*this)(node.data);
  }
};

template <> struct FwdNodeDataProjection<void> {
  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(FwdNode<T> const& node) const noexcept -> T const& {
    return node.data;
  }

  template <typename T> CDS_ATTR(2(nodiscard, constexpr(11)))
  auto operator()(FwdNode<T>& node) const noexcept -> T& {
    return node.data;
  }
};
} // namespace impl
} // namespace cds

#endif // CDS_DS_FWD_NODE_HPP
