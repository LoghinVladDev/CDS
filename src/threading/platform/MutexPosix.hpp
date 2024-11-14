//
// Created by loghin on 11/2/24.
//

#if defined(__linux) || defined(__APPLE__)
#ifndef CDS_THREADING_MUTEX_POSIX_HPP
#define CDS_THREADING_MUTEX_POSIX_HPP
#pragma once

#include <pthread.h>

namespace cds {
namespace impl {
using MutexPlatformHandle = pthread_mutex_t;

inline auto mutexPlatformInit(MutexPlatformHandle* pHandle) noexcept -> void {
  ignore = pthread_mutex_init(pHandle, nullptr);
}

inline auto mutexPlatformDestroy(MutexPlatformHandle* pHandle) noexcept -> void {
  ignore = pthread_mutex_destroy(pHandle);
}

inline auto mutexPlatformLock(MutexPlatformHandle* pHandle) CDS_ATTR(noexcept(false)) -> void {
  // TODO: error handling
  ignore = pthread_mutex_lock(pHandle);
}

inline auto mutexPlatformTryLock(MutexPlatformHandle* pHandle) CDS_ATTR(noexcept(false)) -> bool {
  // TODO: error handling
  return pthread_mutex_trylock(pHandle) == 0;
}

inline auto mutexPlatformUnlock(MutexPlatformHandle* pHandle) CDS_ATTR(noexcept(false)) -> void {
  // TODO: error handling
  ignore = pthread_mutex_unlock(pHandle);
}
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_THREADING_MUTEX_POSIX_HPP
#endif // #if defined(_linux) || defined(__APPLE__)
