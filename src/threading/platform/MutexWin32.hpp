//
// Created by loghin on 11/2/24.
//

#if defined(WIN32)
#ifndef CDS_THREADING_MUTEX_WIN32_HPP
#define CDS_THREADING_MUTEX_WIN32_HPP
#pragma once

//#include <windows.h>
#include <Synchapi.h>

namespace cds {
namespace impl {
using MutexPlatformHandle = CRITICAL_SECTION;

inline auto mutexPlatformInit(MutexPlatformHandle* pHandle) noexcept -> void {
  InitializeCriticalSection(pHandle, nullptr);
}

inline auto mutexPlatformDestroy(MutexPlatformHandle* pHandle) noexcept -> void {
  DeleteCriticalSection(pHandle);
}

inline auto mutexPlatformLock(MutexPlatformHandle* pHandle) CDS_ATTR(noexcept(false)) -> void {
  // TODO: error handling
  EnterCriticalSection(pHandle);
}

inline auto mutexPlatformTryLock(MutexPlatformHandle* pHandle) CDS_ATTR(noexcept(false)) -> bool {
  // TODO: error handling
  return TryEnterCriticalSection(pHandle) != 0;
}

inline auto mutexPlatformUnlock(MutexPlatformHandle* pHandle) CDS_ATTR(noexcept(false)) -> void {
  // TODO: error handling
  LeaveCriticalSection(pHandle);
}
} // namespace impl
} // namespace cds

#endif // #ifndef CDS_THREADING_MUTEX_WIN32_HPP
#endif // #if defined(WIN32)
