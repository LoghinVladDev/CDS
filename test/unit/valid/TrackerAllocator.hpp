//
// Created by loghin on 2/10/24.
//

#ifndef CDS_TEST_TRACKER_ALLOCATOR_HPP
#define CDS_TEST_TRACKER_ALLOCATOR_HPP
#pragma once

#include <cds/meta/Semantics>
#include <cds/memory/Allocator>
#include <cassert>

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
      _assertOnDestruct(cds::exchange(ta._assertOnDestruct, false)) {}

  TrackerAllocator& operator=(TrackerAllocator const&) noexcept = delete;
  TrackerAllocator& operator=(TrackerAllocator&& ta) noexcept {
    if (this == &ta) {
      return *this;
    }

    validate();
    cds::Allocator<T>::operator=(cds::move(ta));
    _allocated = cds::exchange(ta._allocated, 0);
    return *this;
  }

  T* allocate(cds::Size bCnt) noexcept(false) {
    _allocated += sizeof(T) * bCnt;
    return cds::Allocator<T>::allocate(bCnt);
  }

  void deallocate(T* mem, cds::Size bCnt) noexcept {
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
  bool _assertOnDestruct {true};
};
} // namespace testing

#endif // CDS_TEST_TRACKER_ALLOCATOR_HPP
