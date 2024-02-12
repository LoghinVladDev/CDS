//
// Created by loghin on 2/12/24.
//

#ifndef CDS_DS_SINGLE_LINKED_LIST_BASE
#define CDS_DS_SINGLE_LINKED_LIST_BASE
#pragma once

#include <cds/functional/Comparator>
#include <cds/iterator/FwdNodeIterator>

#include "../node/FwdNode.hpp"

namespace cds {
namespace impl {
using meta::rvalue;

using iterator::FwdNodeIterator;

template <typename T, typename C, typename A> class CDS_ATTR(inheritsEBOs) SingleLinkedListBase : private A {
private:
  using Node = FwdNode<T>;

public:
  using Type = T;
  using Alloc = A;

  using Iterator = FwdNodeIterator<T>;
  using ConstIterator = FwdNodeIterator<T const>;

  CDS_ATTR(2(explicit, constexpr(11))) SingleLinkedListBase(Alloc const& alloc = Alloc())
      CDS_ATTR(noexcept(noexcept(A(alloc)))) : A(alloc) {}

  CDS_ATTR(constexpr(20)) SingleLinkedListBase(SingleLinkedListBase const& list)
      CDS_ATTR(noexcept(noexcept(copyOnceClean(list)))) {
    copyOnceClean(list);
  }

  CDS_ATTR(constexpr(14)) SingleLinkedListBase(SingleLinkedListBase&& list) noexcept :
      _f{cds::exchange(list._f, nullptr)}, _b{cds::exchange(list._b, nullptr)} {}

  CDS_ATTR(constexpr(20)) ~SingleLinkedListBase() noexcept {
    clear();
  }

  CDS_ATTR(constexpr(20)) auto clear() noexcept -> void {
    while (_f) {
      auto c = _f;
      _f = _f->next;
      free(c);
    }
    _b = nullptr;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto empty() const noexcept -> bool {
    return !_f;
  }

  CDS_ATTR(constexpr(20)) auto pop() noexcept -> void {
    if (empty()) {
      return;
    }

    auto c = _f;
    _f = _f->next;
    free(c);

    if (!_f) {
      _b = nullptr;
    }
  }

  template <typename... Args> CDS_ATTR(constexpr(20)) auto emplaceFront(Args&&... args)
      CDS_ATTR(noexcept(noexcept(false))) -> Type& {
    _f = construct(alloc(), _f, cds::forward<Args>(args)...);
    if (!_b) {
      _b = _f;
    }
    return _f->data;
  }

  template <typename... Args> CDS_ATTR(constexpr(20)) auto emplaceBack(Args&&... args)
      CDS_ATTR(noexcept(noexcept(false))) -> Type& {
    if (empty()) {
      return emplaceFront(cds::forward<Args>(args)...);
    }

    _b->next = construct(alloc(), nullptr, cds::forward<Args>(args)...);
    _b = _b->next;
    return _b->data;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto begin() noexcept -> Iterator {
    return {_f};
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto end() noexcept -> Iterator {
    return {nullptr};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto begin() const noexcept -> ConstIterator {
    return {_f};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto end() const noexcept -> ConstIterator {
    return {nullptr};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cbegin() const noexcept -> ConstIterator {
    return {_f};
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto cend() const noexcept -> ConstIterator {
    return {nullptr};
  }

protected:
  CDS_ATTR(2(nodiscard, constexpr(11))) auto front() const noexcept -> Type const* {
    return empty() ? nullptr : &_f->data;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto front() noexcept -> Type* {
    return empty() ? nullptr : &_f->data;
  }

  CDS_ATTR(2(nodiscard, constexpr(11))) auto back() const noexcept -> Type const* {
    return empty() ? nullptr : &_b->data;
  }

  CDS_ATTR(2(nodiscard, constexpr(14))) auto back() noexcept -> Type* {
    return empty() ? nullptr : &_b->data;
  }

  CDS_ATTR(constexpr(20)) auto copy(SingleLinkedListBase const& list)
      CDS_ATTR(noexcept(noexcept(copyOnceCleared(list)))) -> void {
    if (&list == this) {
      return;
    }

    clear();
    copyOnceCleared(list);
  }

  CDS_ATTR(constexpr(20)) auto copyOnceCleared(SingleLinkedListBase const& list)
      CDS_ATTR(noexcept(noexcept(false))) -> void {
    auto f = list._f;
    while (f) {
      auto* n = construct(alloc(), nullptr, f->data);
      if (!_b) {
        _f = n;
      } else {
        _b->next = n;
      }
      _b = n;
      f = f->next;
    }
  }

  CDS_ATTR(constexpr(20)) auto move(SingleLinkedListBase&& list)
      CDS_ATTR(noexcept(noexcept(moveOnceCleared(std::move(list))))) -> void {
    if (&list == this) {
      return;
    }

    clear();
    moveOnceCleared(std::move(list));
  }

  CDS_ATTR(constexpr(14)) auto moveOnceCleared(SingleLinkedListBase&& list) noexcept -> void {
    _f = cds::exchange(list._f, nullptr);
    _b = cds::exchange(list._b, nullptr);
    A::operator=(std::move(list));
  }

  CDS_ATTR(constexpr(20)) auto alloc() CDS_ATTR(noexcept(noexcept(rvalue<A>().allocate(1)))) -> Node* {
    return A::allocate(1);
  }

  CDS_ATTR(constexpr(20)) auto free(Node* node) noexcept -> void {
    destruct(node);
    A::deallocate(node, 1);
  }

private:
  Node* _f {nullptr};
  Node* _b {nullptr};
};
} // namespace impl
} // namespace cds

#endif // CDS_DS_SINGLE_LINKED_LIST_BASE
