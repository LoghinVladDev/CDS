//
// Created by loghin on 12/8/23.
//

#ifndef CDS_ITERATOR_HASH_TABLE_ITERATOR_HPP
#define CDS_ITERATOR_HASH_TABLE_ITERATOR_HPP
#pragma once

#include <cds/meta/IteratorTraits>
#include <cds/meta/TypeTraits>

#include "../ds/node/FwdNode.hpp"

#include <cassert>

namespace cds {
namespace iterator {
template <typename T> class HashTableIterator {
public:
  using Traits = meta::NodeIteratorTraits<cds::impl::FwdNode, T>;
  using Node = typename Traits::Node;
  using Value = typename Traits::Value;

  CDS_ATTR(constexpr(11)) HashTableIterator() noexcept : HashTableIterator(nullptr) {};
  CDS_ATTR(constexpr(11)) HashTableIterator(HashTableIterator const&) noexcept = default;
  CDS_ATTR(constexpr(11)) HashTableIterator(HashTableIterator&&) noexcept = default;
  ~HashTableIterator() noexcept = default;

  CDS_ATTR(constexpr(14)) HashTableIterator(Node** bArr, Size bCnt) noexcept :
      _bArr{bArr}, _bCnt{bCnt}, _curr{bArr == nullptr ? nullptr : bArr[0]} {
    assert((bArr == nullptr) == (bCnt == 0) && "Constraint not satisfied -> isNull(bArr) == isZero(bCnt)");
    nextBucket();
  }

  CDS_ATTR(2(implicit, constexpr(11))) HashTableIterator(meta::Nullptr) noexcept :
      _bArr{nullptr}, _bCnt{0}, _curr{nullptr} {}

  CDS_ATTR(constexpr(11)) HashTableIterator(Node** bArr, Size bCnt, Node* curr, Node* prev, Size bIdx) noexcept :
      _bArr{bArr}, _bCnt{bCnt}, _bIdx{bIdx}, _prev{prev}, _curr{curr} {}

  CDS_ATTR(constexpr(14)) auto operator=(HashTableIterator const&) noexcept -> HashTableIterator& = default;
  CDS_ATTR(constexpr(14)) auto operator=(HashTableIterator&&) noexcept -> HashTableIterator& = default;

  CDS_ATTR(constexpr(14)) auto operator++() noexcept -> HashTableIterator& {
    if (_bIdx >= _bCnt) {
      return *this;
    }

    _prev = _curr;
    _curr = _curr->next;
    if (_curr == nullptr) {
      nextBucket();
    }
    return *this;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto operator++(int) noexcept -> HashTableIterator {
    auto copy = *this;
    ++ *this;
    return copy;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator*() const noexcept -> Value& {
    return _curr->data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto operator->() const noexcept -> Value* {
    return &_curr->data;
  }

  template <typename FT> CDS_ATTR(constexpr(11)) friend auto operator==(
      HashTableIterator<FT> const& lhs, HashTableIterator<FT> const& rhs
  ) noexcept -> bool;

  template <typename FT> CDS_ATTR(constexpr(11)) friend auto operator!=(
      HashTableIterator<FT> const& lhs, HashTableIterator<FT> const& rhs
  ) noexcept -> bool;

private:
  CDS_ATTR(constexpr(14)) auto nextBucket() noexcept -> void {
    if (_curr == nullptr) {
      _prev = nullptr;
    }

    while (_curr == nullptr && _bIdx + 1 < _bCnt) {
      _curr = _bArr[++_bIdx];
    }

    if (_bIdx + 1 == _bCnt && _curr == nullptr) {
      ++_bIdx;
    }
  }

  Node** _bArr;
  Size _bCnt;
  Size _bIdx {0u};
  Node* _prev {nullptr};
  Node* _curr;
};

template <typename FT> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator==(
    HashTableIterator<FT> const& lhs, HashTableIterator<FT> const& rhs
) noexcept -> bool {
  return lhs._curr == rhs._curr && lhs._curr != nullptr
      || lhs._curr == rhs._curr && lhs._prev == rhs._prev;
}

template <typename FT> CDS_ATTR(2(nodiscard, constexpr(11))) auto operator!=(
    HashTableIterator<FT> const& lhs, HashTableIterator<FT> const& rhs
) noexcept -> bool {
  return !(lhs == rhs);
}
} // namespace iterator
} // namespace cds

#endif // CDS_ITERATOR_HASH_TABLE_ITERATOR_HPP
