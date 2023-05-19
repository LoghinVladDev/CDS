/* NOLINT(llvm-header-guard)
 * Created by loghin on 23/10/22.
 */

#if defined(WIN32)
#ifndef __CDS_MUTEX_WIN32_HPP__ /* NOLINT(llvm-header-guard) */
#define __CDS_MUTEX_WIN32_HPP__ /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

#include <windows.h>

namespace cds {             /* NOLINT(modernize-concat-nested-namespaces) */
    namespace __hidden {    /* NOLINT(modernize-concat-nested-namespaces, bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
        namespace __impl {  /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            using __MutexPlatformHandleType = CRITICAL_SECTION;   /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */

            inline auto __mutexPlatformInit (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> void {

                (void) InitializeCriticalSection ( pMutexHandle );
            }


            inline auto __mutexPlatformDestroy (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> void {

                (void) DeleteCriticalSection ( pMutexHandle );
            }


            inline auto __mutexPlatformLock (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> void {

                (void) EnterCriticalSection ( pMutexHandle );
            }


            inline auto __mutexPlatformUnlock (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> void {

                (void) LeaveCriticalSection ( pMutexHandle );
            }


            inline auto __mutexPlatformTryLock (    /* NOLINT(bugprone-reserved-identifier, cert-dcl37-c, cert-dcl51-cpp) */
                    __MutexPlatformHandleType * pMutexHandle
            ) noexcept -> bool {

                return TryEnterCriticalSection ( pMutexHandle ) != 0;
            }

        } /* namespace __impl */
    } /* namespace __hidden */
} /* namespace cds */

#endif /* __CDS_MUTEX_WIN32_HPP__ */
#endif
