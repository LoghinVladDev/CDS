//
// Created by loghin on 11/2/24.
//

#ifndef CDS_THREADING_MUTEX_HPP
#define CDS_THREADING_MUTEX_HPP
#pragma once

#include <cds/meta/Compiler>
#include <cds/Tuple>
#include <cds/Utility>

#include "platform/MutexPosix.hpp"
#include "platform/MutexWin32.hpp"

namespace cds {
namespace impl {
using meta::EnableIf;
using meta::Lt;
using meta::Ge;
using meta::Integral;

class Mutex {
public:
  Mutex(Mutex const&) = delete;
  Mutex(Mutex&&) = delete;
  auto operator=(Mutex const&) -> Mutex& = delete;
  auto operator=(Mutex&&) -> Mutex& = delete;

  inline Mutex() noexcept {
    mutexPlatformInit(&_handle);
  }

  inline ~Mutex() noexcept {
    mutexPlatformDestroy(&_handle);
  }

  inline auto lock() CDS_ATTR(noexcept(false)) -> void {
    mutexPlatformLock(&_handle);
  }

  inline auto unlock() CDS_ATTR(noexcept(false)) -> void {
    mutexPlatformUnlock(&_handle);
  }

  inline auto tryLock() CDS_ATTR(noexcept(false)) -> bool {
    return mutexPlatformTryLock(&_handle);
  }

private:
  MutexPlatformHandle _handle;
};

template <
    unsigned start, unsigned end, typename Lock,
    EnableIf<Lt<Integral<unsigned, start>, Integral<unsigned, end>>> = 0
> CDS_ATTR(inline) auto applyLock(Lock& group)
    CDS_ATTR(noexcept(false)) -> void {
  CDS_ATTR(try) {
    get<start>(group).lock();
    applyLock<start + 1, end>(group);
  } CDS_ATTR(catch(..., {
    get<start>(group).unlock();
    throw;
  }))
}

template <
    unsigned start, unsigned end, typename Lock,
    EnableIf<Ge<Integral<unsigned, start>, Integral<unsigned, end>>> = 0
> CDS_ATTR(inline) auto applyLock(Lock& group)
    CDS_ATTR(noexcept(false)) -> void {
  ignore = group;
}

template <
    unsigned start, unsigned end, typename Lock,
    EnableIf<Lt<Integral<unsigned, start>, Integral<unsigned, end>>> = 0
> CDS_ATTR(inline) auto removeLock(Lock& group)
CDS_ATTR(noexcept(false)) -> void {
  removeLock<start + 1, end>(group);
  get<start>(group).unlock();
}

template <
    unsigned start, unsigned end, typename Lock,
    EnableIf<Ge<Integral<unsigned, start>, Integral<unsigned, end>>> = 0
> CDS_ATTR(inline) auto removeLock(Lock& group)
CDS_ATTR(noexcept(false)) -> void {
  ignore = group;
}

template <typename... Lockable> class Lock {
public:
  Lock() = delete;
  Lock(Lock const&) = delete;
  Lock(Lock&&) = delete;
  auto operator=(Lock const&) -> Lock& = delete;
  auto operator=(Lock&&) -> Lock& = delete;

  CDS_ATTR(2(explicit, inline)) Lock(Lockable&... lockableObjects) CDS_ATTR(noexcept(false)) :
      _objects{lockableObjects...} {
    applyLock<0, sizeof...(Lockable)>(_objects);
  }

  ~Lock() CDS_ATTR(noexcept(false)) {
    removeLock<0, sizeof...(Lockable)>(_objects);
  }

private:
  Tuple<Lockable&...> _objects;
};

#if CDS_ATTR(ctad)
template <typename... Lockable> Lock(Lockable&...) -> Lock<Lockable...>;
#endif
} // namespace impl

using impl::Mutex;
using impl::Lock;
} // namespace cds

#endif // CDS_THREADING_MUTEX_HPP
