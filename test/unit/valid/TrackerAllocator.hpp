//
// Created by loghin on 2/10/24.
//

#ifndef CDS_TEST_TRACKER_ALLOCATOR_HPP
#define CDS_TEST_TRACKER_ALLOCATOR_HPP
#pragma once

#include <cds/meta/Semantics>
#include <cds/memory/Allocator>
#include <cassert>
#include <unordered_set>

#if defined(NDEBUG) && CDS_ATTR(libcxx)
#include <exception>
#endif

namespace testing {
template <typename T> class TrackerAllocator : public cds::Allocator<T> {
public:
  TrackerAllocator() noexcept = default;
  explicit TrackerAllocator(bool assertOnDestruct) noexcept : _assertOnDestruct(assertOnDestruct) {}
  TrackerAllocator(TrackerAllocator const& ta) noexcept :
      cds::Allocator<T>(ta),
      _assertOnDestruct(ta._assertOnDestruct) {}

  TrackerAllocator(TrackerAllocator&& ta) noexcept :
      cds::Allocator<T>(cds::move(ta)),
      _allocated(cds::exchange(ta._allocated, 0u)),
      _tracked(std::move(ta._tracked)),
      _freed(std::move(ta._freed)),
      _assertOnDestruct(cds::exchange(ta._assertOnDestruct, false)) {}

  TrackerAllocator& operator=(TrackerAllocator const&) noexcept = delete;
  TrackerAllocator& operator=(TrackerAllocator&& ta) noexcept {
    if (this == &ta) {
      return *this;
    }

    validate();
    cds::Allocator<T>::operator=(cds::move(ta));
    _allocated = cds::exchange(ta._allocated, 0);
    _tracked = std::move(ta._tracked);
    _freed = std::move(ta._freed);
    return *this;
  }

  T* allocate(cds::Size bCnt) noexcept(false) {
    _allocated += sizeof(T) * bCnt;
    auto ptr = cds::Allocator<T>::allocate(bCnt);
    _tracked.emplace(ptr);
    _freed.erase(ptr);
    return ptr;
  }

  void deallocate(T* mem, cds::Size bCnt) noexcept {
    if (_freed.find(mem) != _freed.end()) {
#if NDEBUG
      std::cerr << "Double free of memory from current allocator\n";
      std::cerr.flush();
      std::terminate();
#endif
      assert(false && "Double free attempted");
    }

    if (_tracked.find(mem) != _freed.end()) {
      _tracked.erase(mem);
      _freed.emplace(mem);
    } else if (mem) {
#if NDEBUG
      std::cerr << "Attempted to free memory not allocated from current allocator\n";
      std::cerr.flush();
      std::terminate();
#endif
      assert(false && "Attempted to free memory not allocated from this allocator");
    }

    cds::Allocator<T>::deallocate(mem, bCnt);
    _allocated -= sizeof(T) * bCnt;
  }

  ~TrackerAllocator() {
    validate();
  }

  void validate() noexcept {
    if (_assertOnDestruct && _allocated != 0) {
#if NDEBUG
      std::cerr << "Memory leaked in release\n";
      std::cerr.flush();
      std::terminate();
#endif
      assert(false && "Memory leaked");
    }
  }

  CDS_ATTR(nodiscard) cds::Size committed() const noexcept {
    return _allocated;
  }

private:
  cds::Size _allocated {0u};
  std::unordered_set<T*> _tracked;
  std::unordered_set<T*> _freed;
  bool _assertOnDestruct {true};
};
} // namespace testing

#endif // CDS_TEST_TRACKER_ALLOCATOR_HPP
