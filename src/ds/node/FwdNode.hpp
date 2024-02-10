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
      CDS_ATTR(noexcept(noexcept(T(cds::forward<A>(args)...)))) :
      next{n}, data{cds::forward<A>(args)...} {}
};
} // namespace impl
} // namespace cds

#endif // CDS_DS_FWD_NODE_HPP
