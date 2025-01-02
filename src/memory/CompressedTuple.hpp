//
// Created by vloghin on 26.12.2024.
//

#ifndef CDS_MEMORY_COMPRESSED_PAIR_HPP
#define CDS_MEMORY_COMPRESSED_PAIR_HPP
#pragma once

#include <cds/meta/TypeTraits>
#include <cds/meta/Semantics>

namespace cds {
namespace impl {
using meta::And;
using meta::IsEmpty;
using meta::IsFinal;
using meta::Not;
using meta::True;
template <typename T, unsigned idx, typename = typename And<IsEmpty<T>, Not<IsFinal<T>>>::Type>
class CDS_ATTR(ebo) CompressedTupleNode : private T {
public:
  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) CompressedTupleNode(Args&&... args)
      CDS_ATTR(noexcept(noexcept(T{fwd<Args>(args)...}))) : T{fwd<Args>(args)...} {}

  CompressedTupleNode(CompressedTupleNode const&) = default;
  CompressedTupleNode(CompressedTupleNode&&) = default;
  auto operator=(CompressedTupleNode const&) -> CompressedTupleNode& = default;
  auto operator=(CompressedTupleNode&&) -> CompressedTupleNode& = default;
  ~CompressedTupleNode() = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto get() const noexcept -> T const& {
    return *static_cast<T const*>(this);
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto get() noexcept -> T& {
    return *static_cast<T*>(this);
  }
};

template <typename T, unsigned idx> class CompressedTupleNode<T, idx, True> {
public:
  template <typename... Args> CDS_ATTR(2(explicit, constexpr(11))) CompressedTupleNode(Args&&... args)
      CDS_ATTR(noexcept(noexcept(T{fwd<Args>(args)...}))) : _elem{fwd<Args>(args)...} {}

  CompressedTupleNode(CompressedTupleNode const&) = default;
  CompressedTupleNode(CompressedTupleNode&&) = default;
  auto operator=(CompressedTupleNode const&) -> CompressedTupleNode& = default;
  auto operator=(CompressedTupleNode&&) -> CompressedTupleNode& = default;
  ~CompressedTupleNode() = default;

  CDS_ATTR(2(nodiscard, constexpr(11))) auto get() const noexcept -> T const& {
    return _elem;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto get() noexcept -> T& {
    return _elem;
  }

private:
  T _elem;
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_MEMORY_COMPRESSED_PAIR_HPP
