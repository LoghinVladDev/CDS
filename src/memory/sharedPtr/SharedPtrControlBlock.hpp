//
// Created by vloghin on 24.12.2024.
//

#ifndef CDS_MEMORY_SHARED_PTR_CONTROL_BLOCK_HPP
#define CDS_MEMORY_SHARED_PTR_CONTROL_BLOCK_HPP
#pragma once

#include <cds/threading/Atomic>
#include <cds/Utility>

namespace cds {
namespace impl {
class SharedOwnerControlBlock {
public:
  SharedOwnerControlBlock(SharedOwnerControlBlock const&) = delete;
  SharedOwnerControlBlock(SharedOwnerControlBlock&&) = delete;
  auto operator=(SharedOwnerControlBlock const&) -> SharedOwnerControlBlock& = delete;
  auto operator=(SharedOwnerControlBlock&&) -> SharedOwnerControlBlock& = delete;
  virtual ~SharedOwnerControlBlock() noexcept = default;

  CDS_ATTR(inline) SharedOwnerControlBlock() noexcept : _owners{1u} {}

  CDS_ATTR(inline) auto acquireShared() noexcept -> void {
    ignore = _owners.fetchAdd(1u, AtomicMemoryOrder::Relaxed);
  }

  CDS_ATTR(inline) auto releaseShared() noexcept -> bool {
    if (0u != _owners.fetchSub(1u, AtomicMemoryOrder::AcqRel)) {
      return false;
    }
    exitScope();
    return true;
  }

  CDS_ATTR(inline) auto useCount() const noexcept -> Size {
    return static_cast<Size>(_owners.load(AtomicMemoryOrder::Relaxed));
  }

private:
  virtual auto exitScope() noexcept -> void = 0;
  Atomic<U32> _owners;
};

class SharedObserverControlBlock : private SharedOwnerControlBlock {
public:
  SharedObserverControlBlock(SharedObserverControlBlock const&) = delete;
  SharedObserverControlBlock(SharedObserverControlBlock&&) = delete;
  auto operator=(SharedObserverControlBlock const&) = delete;
  auto operator=(SharedObserverControlBlock&&) = delete;

  CDS_ATTR(inline) SharedObserverControlBlock() noexcept : SharedOwnerControlBlock{}, _observers{1u} {}

  using SharedOwnerControlBlock::acquireShared;
  using SharedOwnerControlBlock::useCount;

  CDS_ATTR(inline) auto acquireWeak() noexcept -> void {
    ignore = _observers.fetchAdd(1u, AtomicMemoryOrder::Relaxed);
  }

  CDS_ATTR(inline) auto releaseShared() noexcept -> void {
    if (SharedOwnerControlBlock::releaseShared()) {
      releaseWeak();
    }
  }

  CDS_ATTR(inline) auto releaseWeak() noexcept -> void {
    if (1u == _observers.load(AtomicMemoryOrder::Acquire)) {
      exitWeakScope();
    } else if (0u == _observers.fetchSub(1u, AtomicMemoryOrder::AcqRel)) {
      exitWeakScope();
    }
  }

private:
  virtual auto exitWeakScope() noexcept -> void = 0;

  Atomic<U32> _observers;
};

template <typename T, typename D, typename A> class ReceivingSharedControlBlock :
    public SharedObserverControlBlock, private D, private A {
public:
  CDS_ATTR(inline) ReceivingSharedControlBlock(T obj, D dtr, A alloc) CDS_ATTR(noexcept(
      noexcept(D{mv(dtr)}) && noexcept(A{mv(alloc)})
  )) : SharedObserverControlBlock{}, D{mv(dtr)}, A{mv(alloc)}, _obj{obj} {}

private:
  auto exitScope() noexcept -> void override {
    auto&& dtr = *static_cast<D*>(this);
    dtr(_obj);
  }

  auto exitWeakScope() noexcept -> void override {
    auto alloc = mv(*static_cast<A*>(this));
    alloc.deallocate()
  }

  T _obj;
};
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_MEMORY_SHARED_PTR_CONTROL_BLOCK_HPP
