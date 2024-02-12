//
// Created by loghin on 2/12/24.
//

#ifndef CDS_ITERATOR_FWD_NODE_ITERATOR_HPP
#define CDS_ITERATOR_FWD_NODE_ITERATOR_HPP

#include <cds/meta/IteratorTraits>

#include "../ds/node/FwdNode.hpp"

namespace cds {
namespace iterator {
template <typename T> class FwdNodeIterator {
public:
  using Traits = meta::NodeIteratorTraits<cds::impl::FwdNode, T>;
  using Node = typename Traits::Node;
  using Value = typename Traits::Value;

  CDS_ATTR(constexpr(11)) FwdNodeIterator() noexcept : FwdNodeIterator(nullptr) {}
  CDS_ATTR(constexpr(11)) FwdNodeIterator(FwdNodeIterator const&) noexcept = default;
  CDS_ATTR(constexpr(11)) FwdNodeIterator(FwdNodeIterator&&) noexcept = default;
  ~FwdNodeIterator() noexcept = default;

  CDS_ATTR(2(implicit, constexpr(11))) FwdNodeIterator(Node* node) noexcept : _n{node} {}

  CDS_ATTR(constexpr(14)) auto operator=(FwdNodeIterator const&) noexcept -> FwdNodeIterator& = default;
  CDS_ATTR(constexpr(14)) auto operator=(FwdNodeIterator&&) noexcept -> FwdNodeIterator& = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const noexcept -> Value& {
    return _n->data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator->() const noexcept -> Value* {
    return _n->data;
  }

  CDS_ATTR(constexpr(14)) auto operator++() noexcept -> FwdNodeIterator& {
    _n = _n->next;
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator++(int) noexcept -> FwdNodeIterator {
    auto copy = *this;
    _n = _n->next;
    return copy;
  }

  template <typename FT> CDS_ATTR(constexpr(11)) friend auto operator==(
      FwdNodeIterator<FT> const& lhs, FwdNodeIterator<FT> const& rhs
  ) noexcept -> bool;

  template <typename FT> CDS_ATTR(constexpr(11)) friend auto operator!=(
      FwdNodeIterator<FT> const& lhs, FwdNodeIterator<FT> const& rhs
  ) noexcept -> bool;

private:
  Node* _n;
};

template <typename FT> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    FwdNodeIterator<FT> const& lhs, FwdNodeIterator<FT> const& rhs
) noexcept -> bool {
  return lhs._n == rhs._n;
}

template <typename FT> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    FwdNodeIterator<FT> const& lhs, FwdNodeIterator<FT> const& rhs
) noexcept -> bool {
  return lhs._n != rhs._n;
}
} // namespace iterator
} // namespace cds

#endif // CDS_ITERATOR_FWD_NODE_ITERATOR_HPP
